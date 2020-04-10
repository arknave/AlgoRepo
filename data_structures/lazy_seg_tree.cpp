// Credit: saketh-are
struct lazy_seg_tree {
    using T = array<ll, 3>;
    using U = ll;
    const T unit = T{0, INF, 0};
    const U noop = 0;

    // T + T
    T f(const T& a, const T& b) const {
        return {a[0] + b[0], min(a[1], b[1]), a[2] + b[2]};
    }

    // T + U
    T g(const T& a, const U& b) const {
        return {a[0] + a[2] * b, a[1] + b, a[2]};
    }

    // U + U
    U h(const U& a, const U& b) const {
        return a + b;
    }

    int n;
    vector<T> table;
    vector<bool> has; vector<U> ops;

    lazy_seg_tree(int n): n(n) {
        table.resize(n + n, unit), has.resize(n), ops.resize(n, noop);
    }

    template <typename L>
    void set_leaves(L create) {
        for (int i = 0; i < n; ++i) {
            table[n + i] = create(i);
        }
        for (int i = n - 1; i > 0; --i) {
            table[i] = f(table[2 * i], table[2 * i + 1]);
        }
    }

    void apply(int i, const U &op) {
        table[i] = g(table[i], op);
        if (i < n) has[i] = true, ops[i] = h(op, ops[i]);
    }

    void rebuild(int i) {
        for (i /= 2; i; i /= 2)
            table[i] = g(f(table[2 * i], table[2 * i + 1]), ops[i]);
    }

    void propagate(int i) {
        for (int j = 31 - __builtin_clz(i); j > 0; j--) {
            int k = i >> j;
            if (has[k]) {
                apply(2 * k, ops[k]);
                apply(2 * k + 1, ops[k]);
                has[k] = false, ops[k] = noop;
            }
        }
    }

    // Replaces the element at index i with v
    void replace(int i, T v) {
        i += n;
        propagate(i);
        table[i] = v;
        rebuild(i);
    }

    // Applies op to the elements at indices in [i, j)
    void update(int i, int j, U op) {
        i += n, j += n;
        propagate(i), propagate(j - 1);
        for (int l = i, r = j; l < r; l /= 2, r /= 2) {
            if (l & 1) apply(l++, op);
            if (r & 1) apply(--r, op);
        }
        rebuild(i), rebuild(j - 1);
    }

    // Returns the element at index i
    const T& operator[](int i) {
        i += n;
        propagate(i);
        return table[i];
    }

    // query [i, j)
    T query(int i, int j) {
        i += n, j += n;
        propagate(i), propagate(j - 1);
        T left = unit, right = unit;
        for (; i < j; i /= 2, j /= 2) {
            if (i & 1) left  = f(left, table[i++]);
            if (j & 1) right = f(table[--j], right);
        }
        return f(left, right);
    }
};
