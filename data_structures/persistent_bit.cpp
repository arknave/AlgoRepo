// 0 indexed template
struct P_BIT {
    using T = int32_t;
    static constexpr T MIN_VAL = std::numeric_limits<T>::min();
    int32_t n, id;
    // id, val
    std::vector<std::vector<std::pair<int32_t, T>>> f_tree;

    constexpr static T op(T a, T b) {
        return a + b;
    }

    P_BIT(int32_t n): n(n), id(0) {
        f_tree.resize(n + 1);
    }

    void update(int32_t x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            if (f_tree[x].empty()) {
                f_tree[x].emplace_back(id, v);
            } else if (f_tree[x].back().first == id) {
                f_tree[x].back().second = op(f_tree[x].back().second, v);
            } else {
                f_tree[x].emplace_back(id, op(f_tree[x].back().second, v));
            }
        }
    }

    // query [0, x] only considering values before day d
    T query(int32_t x, int32_t d) const {
        T res = 0;
        for (++x; x > 0; x -= (x & -x)) {
            auto it = std::lower_bound(f_tree[x].begin(), f_tree[x].end(), std::pair<int32_t, T>{d + 1, MIN_VAL});
            if (it != std::begin(f_tree[x])) {
                res = op(res, std::prev(it)->second);
            }
        }

        return res;
    }

    void step() {
        ++id;
    }
};
