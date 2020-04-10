struct seg_tree {
    using T = int;
    static constexpr T unit = INT_MIN;
    T f(T a, T b) { return max(a, b); }

    int n;
    vector<T> data;
    seg_tree(int n): n(n) {
        data.assign(n << 1, unit);
    }

    void update(int i, T v) {
        i += n;
        data[i] = v;
        for (i >>= 1; i; i >>= 1) {
            data[i] = f(data[i << 1], data[i << 1 | 1]);
        }
    }

    T query(int l, int r) {
        T res_left = unit, res_right = unit;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)    res_left  = f(res_left , data[l++]);
            if (!(r & 1)) res_right = f(data[r--], res_right);
        }

        return f(res_left, res_right);
    }
};
