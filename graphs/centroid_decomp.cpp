// Fill out process()

template <typename T>
struct CentroidDecomp {
    CentroidDecomp(T&& tree)
        : tree_(std::move(tree))
        , vis_(tree_.size(), false)
        , size_(tree_.size()) {

        centroid(0);
    }

    void process(int32_t u) {
        // TODO: Fill in
        // don't forget to skip visited vertices if doing another DFS
    }

    void dfsSize(int32_t u, int32_t p) {
        size_[u] = 1;
        for (auto [v, w] : tree_[u]) {
            if (vis_[v] || v == p)
                continue;

            dfsSize(v, u);
            size_[u] += size_[v];
        }
    };

    int32_t findCenter(int32_t total, int32_t u, int32_t p) {
        for (auto [v, w] : tree_[u]) {
            if (vis_[v] || v == p) {
                continue;
            }

            if (2 * size_[v] >= total) {
                return findCenter(total, v, u);
            }
        }

        return u;
    }

    void centroid(int32_t u) {
        dfsSize(u, -1);
        int32_t c = findCenter(size_[u], u, -1);

        process(c);

        vis_[c] = true;
        for (auto [v, w] : tree_[c]) {
            if (!vis_[v]) {
                centroid(v);
            }
        }
    }

    T tree_;
    std::vector<bool> vis_;
    std::vector<int32_t> size_;
};
