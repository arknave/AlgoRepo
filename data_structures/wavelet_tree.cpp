/**
 * Structure to answer k-th queries. Basic idea is like a segment tree, but
 * each child has half of the values instead of half of the indices.
 *
 * [lo, hi)
 * Tested: https://www.spoj.com/problems/MKTHNUM/
 */
struct WaveletTree {
    vector<size_t> build_idxs(size_t n) {
        vector<size_t> _idxs(n);
        iota(_idxs.begin(), _idxs.end(), 0);

        return _idxs;
    }

    WaveletTree(const vector<int64_t>& v, const vector<size_t>& idxs, int64_t lo, int64_t hi): lo(lo), hi(hi), idxs(idxs), left_sum(1, 0) {
        if (is_leaf()) {
            return;
        }

        int64_t mid = (lo + hi) / 2;

        vector<size_t> lo_idxs, hi_idxs;
        left_sum.reserve(idxs.size() + 1);
        for (size_t idx : idxs) {
            if (v[idx] < mid) {
                lo_idxs.push_back(idx);
                left_sum.push_back(left_sum.back() + 1);
            } else {
                hi_idxs.push_back(idx);
                left_sum.push_back(left_sum.back());
            }
        }

        children[0] = make_unique<WaveletTree>(v, lo_idxs, lo, mid);
        children[1] = make_unique<WaveletTree>(v, hi_idxs, mid, hi);
    }

    WaveletTree(const vector<int64_t>& v) : 
        WaveletTree(v, 
                    build_idxs(v.size()), 
                    *min_element(v.begin(), v.end()),
                    *max_element(v.begin(), v.end()) + 1) {}

    bool is_leaf() const {
        return lo + 1 == hi || idxs.empty();
    }

    // Find the index of the k-th smallest value in the range [l, r)
    // k is 0 indexed.
    // Returns -1 on failure
    ssize_t kth(size_t l, size_t r, size_t k) {
        if (is_leaf()) {
            return k < idxs.size() ? idxs[k] : -1;
        }

        int32_t in_left = left_sum[r] - left_sum[l];
        if (k < in_left) {
            return children[0]->kth(left_sum[l], left_sum[r], k);
        } else {
            return children[1]->kth(l - left_sum[l], r - left_sum[r], k - in_left);
        }
    }

    int64_t lo;
    int64_t hi;
    vector<size_t> idxs;
    // left_sum[i] = # of the first i indexes <= mid
    vector<int32_t> left_sum;
    array<unique_ptr<WaveletTree>, 2> children;
};
