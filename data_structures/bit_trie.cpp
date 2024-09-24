struct Trie {
    // must be unsigned
    using T = uint64_t;
    static constexpr int BITS = std::numeric_limits<T>::digits;

    T numNodes;
    std::vector<std::array<T, 2>> data;
    std::vector<T> hits;

    Trie(): numNodes(1) {
        data.push_back({0, 0});
        hits.push_back(0);
    }

    void insert(T x) {
        T node = 0;
        for (T bit = BITS - 1; bit < BITS; --bit) {
            bool b = x >> bit & 1;
            if (!data[node][b]) {
                data[node][b] = numNodes++;
                data.push_back({0, 0});
                hits.push_back(0);
            }

            node = data[node][b];
            ++hits[node];
        }
    }

    void remove(T x) {
        T node = 0;
        for (T bit = BITS - 1; bit < BITS; --bit) {
            bool b = x >> bit & 1;
            assert(data[node][b] != 0);
            node = data[node][b];
            --hits[node];
        }
    }

    // Find the y that maximizes x ^ y
    T query(u64 x) {
        T node = 0;
        T res = 0;
        for (T bit = BITS - 1; bit < BITS; --bit) {
            bool b = x >> bit & 1;
            if (hits[data[node][b ^ 1]]) {
                res ^= (1ULL << bit);
                node = data[node][b ^ 1];
            } else {
                node = data[node][b];
            }
        }

        return res ^ x;
    }
};
