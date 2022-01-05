// 0 indexed template
struct P_BIT {
    using T = int;
    constexpr T MIN_VAL = -0x3f3f3f3f;
    int n, id;
    // id, val
    vector<vector<pair<int, T>>> f_tree;

    inline T op(T a, T b) const {
        return a + b;
    }

    P_BIT(int n): n(n), id(0) {
        f_tree.resize(n + 1);
    }

    void update(int x, T v) {
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
    T query(int x, int d) const {
        T res = 0;
        for (++x; x; x -= (x & -x)) {
            auto it = lower_bound(all(f_tree[x]), pair<int, T>{d + 1, MIN_VAL);
            if (it != begin(f_tree[x])) {
                res = op(res, prev(it)->second);
            }
        }

        return res;
    }

    inline void step() {
        ++id;
    }
};
