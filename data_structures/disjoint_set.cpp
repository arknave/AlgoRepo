struct DSU {
    int32_t n;
    // uf[x] = parent of x or negative size of component
    std::vector<int32_t> uf;
    DSU(int32_t n): n(n) {
        uf.assign(n, -1);
    }

    int32_t find(int32_t x) {
        return uf[x] < 0 ? x : (uf[x] = find(uf[x]));
    }

    int32_t merge(int32_t x, int32_t y) {
        int32_t xr = find(x);
        int32_t yr = find(y);
        if (xr == yr)
            return 0;

        if (uf[yr] < uf[xr]) {
            uf[yr] += uf[xr];
            uf[xr] = yr;
        } else {
            uf[xr] += uf[yr];
            uf[yr] = xr;
        }

        return 1;
    }

    int32_t get_size(int32_t x) {
        return -uf[find(x)];
    }

    bool is_same(int32_t x, int32_t y) {
        return find(x) == find(y);
    }

    std::vector<std::vector<int32_t>> getComps() {
        std::vector<std::vector<int32_t>> comps;
        std::vector<int32_t> comp_id(n, -1);
        for (int32_t i = 0; i < n; ++i) {
            int32_t root = find(i);
            if (comp_id[root] == -1) {
                comp_id[root] = comps.size();
                comps.push_back({});
            }

            comps[comp_id[root]].push_back(i);
        }

        return comps;
    }
};
