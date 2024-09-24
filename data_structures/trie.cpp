struct Trie {
    static constexpr char BASE = 'a';
    static constexpr uint32_t SIGMA = 26;

    Trie(): size_{1}, data_(1), freq_(1, 0) {
        std::fill(data_[0].begin(), data_[0].end(), 0u);
    }

    uint32_t addNode() {
        data_.push_back({});
        freq_.push_back(0);

        return size_++;
    }

    void insert(std::string_view s) {
        uint32_t curNode = 0;
        for (char c : s) {
            uint32_t idx = c - BASE;
            if (data_[curNode][idx] == 0) {
                data_[curNode][idx] = addNode();
            }

            curNode = data_[curNode][idx];
            ++freq_[curNode];
        }
    }

    int32_t query(std::string_view s) const {
        uint32_t curNode = 0;
        for (char c : s) {
            uint32_t idx = c - BASE;
            if (data_[curNode][idx] == 0) {
                return 0;
            }

            curNode = data_[curNode][idx];
        }

        return freq_[curNode];
    }

    uint32_t size_;
    std::vector<std::array<uint32_t, SIGMA>> data_;
    std::vector<int32_t> freq_;
};
