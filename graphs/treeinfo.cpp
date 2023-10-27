// TODO: Make general
struct TreeInfo {
    TreeInfo(const auto& tree, int32_t root = 0) : n(tree.size()), timestamp(0), depth(n), timeIn(n), timeOut(n) {
        depth[root] = 0;

        for (logn = 0; (1 << logn) <= n;)
            ++logn;

        sparseTable.assign(logn, std::vector<int32_t>(n, -1));
        dfs(tree, root);

        assert(timestamp == n);

        for (size_t j = 0; j + 1 < logn; ++j) {
            for (size_t u = 0; u < n; ++u) {
                if (sparseTable[j][u] != -1) {
                    sparseTable[j + 1][u] = sparseTable[j][sparseTable[j][u]];
                }
            }
        }
    }

    void dfs(const auto& tree, int32_t u) {
        timeIn[u] = timestamp++;
        for (auto v : tree[u]) if (v != parent(u)) {
            sparseTable[0][v] = u;
            depth[v] = depth[u] + 1;
            dfs(tree, v, u);
        }

        timeOut[u] = timestamp;
    }

    int32_t lca(int32_t u, int32_t v) const {
        if (depth[u] > depth[v]) {
            std::swap(u, v);
        }

        for (int32_t j = logn - 1; j >= 0; --j) {
            if (depth[v] - (1 << j) >= depth[u]) {
                v = sparseTable[j][v];
            }
        }

        assert(depth[u] == depth[v]);
        assert(u != -1 && v != -1);

        if (u == v) {
            return u;
        }

        for (int32_t j = logn - 1; j >= 0; --j) {
            if (sparseTable[j][u] != sparseTable[j][v]) {
                u = sparseTable[j][u];
                v = sparseTable[j][v];
            }
        }

        return sparseTable[0][u];
    }

    inline int32_t parent(int32_t u) const { return sparseTable[0][u]; }

    bool doPathsIntersect(int32_t u1, int32_t v1, int32_t u2, int32_t v2) {
        int32_t w1 = lca(u1, v1);
        int32_t w2 = lca(u2, v2);

        return onPath(w1, w2, u2) || onPath(w1, w2, v2) || onPath(w2, w1, u1) || onPath(w2, w1, v1);
    };

    // is u in between up and down where up is an ancestor of down
    inline bool onPath(int32_t u, int32_t up, int32_t down) {
        assert(inSubtree(up, down));
        return inSubtree(up, u) && inSubtree(u, down);
    }

    // is v in the subtree of u
    inline bool inSubtree(int32_t u, int32_t v) const {
        return (timeIn[u] <= timeIn[v]) && (timeIn[v] < timeOut[u]);
    }

    int32_t n, root, logn, timestamp;
    // depth[u] - number of edges between 0 and u
    std::vector<int32_t> depth, timeIn, timeOut;

    // st[j][u] = 2^jth ancestor of u
    std::vector<std::vector<int32_t>> sparseTable;
};
