template <typename T>
struct seg_tree {
    int n;
    vector<T> data;
    seg_tree(int n): n(n) {
        data.resize(n << 1);
    }

    // init the seg tree in O(n)
    void set_leaves(const vector<T>& leaves) {
        for (int i = 0; i < n; ++i) {
            data[i + n] = leaves[i];
        }

        for (int i = n - 1; i; --i) {
            data[i] = data[i << 1] + data[i << 1 | 1];
        }
    }

    void update(int i, T v) {
        i += n;
        data[i] = v;
        for (i >>= 1; i; i >>= 1) {
            data[i] = data[i << 1] + data[i << 1 | 1];
        }
    }

    T query(int l, int r) {
        T res_left, res_right;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)    res_left  = res_left  + data[l++];
            if (!(r & 1)) res_right = data[r--] + res_right;
        }

        return res_left + res_right;
    }
};


