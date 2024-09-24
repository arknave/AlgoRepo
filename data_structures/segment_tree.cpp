// zero indexed
struct SegTree {
    using T = int64_t;
    static constexpr T UNIT = std::numeric_limits<T>::min();
    T f(T a, T b) { return std::max(a, b); }

    int32_t n;
    std::vector<T> data;
    SegTree(int32_t n): n(n) {
        data.assign(2 * n, UNIT);
    }

    // a[i] = v
    void update(int32_t i, T v) {
        i += n;
        data[i] = v;
        for (i >>= 1; i; i >>= 1) {
            data[i] = f(data[i << 1], data[i << 1 | 1]);
        }
    }

    // query [l, r)
    T query(int32_t l, int32_t r) {
        T res_left = UNIT, res_right = UNIT;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_left  = f(res_left , data[l++]);
            if (r & 1) res_right = f(data[--r], res_right);
        }

        return f(res_left, res_right);
    }
};
