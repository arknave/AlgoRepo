struct Trie {
    static constexpr int LOGN = 61;

    int next_node;
    vector<vector<int>> data;
    vector<int> hits;

    Trie(): next_node(1) {
        data.emplace_back(2, 0);
        hits.push_back(0);
    }

    void insert(ll x) {
        int node = 0;
        for (ll bit = LOGN - 1; bit >= 0; --bit) {
            bool b = (x & (1LL << bit)) > 0;
            if (!data[node][b]) {
                data[node][b] = next_node++;
                data.emplace_back(2, 0);
                hits.push_back(0);
            }

            node = data[node][b];
            ++hits[node];
        }
    }

    void remove(ll x) {
        int node = 0;
        for (ll bit = LOGN - 1; bit >= 0; --bit) {
            bool b = (x & (1LL << bit)) > 0;
            assert(data[node][b] != 0);
            node = data[node][b];
            --hits[node];
        }
    }

    // Find the y that maximizes x ^ y
    ll query(ll x) {
        int node = 0;
        ll res = 0LL;
        for (ll bit = LOGN - 1; bit >= 0; --bit) {
            bool b = (x & (1LL << bit)) > 0;
            if (hits[data[node][b ^ 1]]) {
                res ^= (1LL << bit);
                node = data[node][b ^ 1];
            } else {
                node = data[node][b];
            }
        }

        return res ^ x;
    }
};
