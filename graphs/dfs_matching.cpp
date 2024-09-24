#pragma once

struct DFSMatching {
    DFSMatching(int32_t n, int32_t m): n_(n), m_(m), graph_(n), rev_(m, -1), vis_(m, 0) {}

    void addEdge(int32_t u, int32_t v) {
        graph_[u].push_back(v);
    }

    bool find(int32_t j) {
        if (rev_[j] == -1) return true;
        vis_[j] = true;
        int32_t i = rev_[j];
        for (auto k : graph_[i]) {
            if (!vis_[k] && find(k)) {
                rev_[k] = i;
                return true;
            }
        }

        return false;
    }

    int32_t dfsMatching() {
        for (auto i = 0; i < n_; ++i) {
            std::fill(vis_.begin(), vis_.end(), 0);
            for (auto j : graph_[i]) {
                if (find(j)) {
                    rev_[j] = i;
                    break;
                }
            }
        }

        return m_ - std::count(rev_.begin(), rev_.end(), -1);
    }

    int32_t n_, m_;
    std::vector<std::vector<int32_t>> graph_;
    std::vector<int32_t> rev_;
    std::vector<char> vis_;
};
