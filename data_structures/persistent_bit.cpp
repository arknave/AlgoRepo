// 0 indexed template
struct P_BIT {
    using T = int;
    int n, id;
    // id, val
    vector<vector<pair<int, T>>> f_tree;

    P_BIT(int n): n(n), id(0) {
        f_tree.resize(n + 1);
    }

    void update(int x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            if (f_tree[x].empty()) {
                f_tree[x].emplace_back(id, v);
            } else {
                f_tree[x].emplace_back(id, f_tree[x].back().first + v);
            }
        }
    }

    // query [0, x] only considering values before day d
    T query(int x, int d) const {
        T res = 0;
        for (++x; x; x -= (x & -x)) {
            auto it = upper_bound(all(f_tree[x]), pair<int, T>{d, -1});
            if (it != begin(f_tree[x])) {
                res = res + prev(it)->second;
            }
        }

        return res;
    }

    inline T query(int l, int r, int d) const {
        return query(r, d) - query(l - 1, d);
    }

    inline void step() {
        ++id;
    }
};
