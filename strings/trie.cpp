// Use a dynamic vector for the children, and iterate over
// all children to find next node. Faster for large (>30) alphabet sizes
class Trie {
public:
    Trie(): children_(1), hits_(1, 0) {}

    uint32_t create(uint32_t node, uint32_t x) {
        uint32_t next_node = children_.size();
        children_[node].emplace_back(next_node, x);
        children_.emplace_back();
        hits_.push_back(0);

        return next_node;
    }

    uint32_t follow(uint32_t node, uint32_t x) const {
        for (auto [idx, val] : children_[node]) {
            if (val == x) {
                return idx;
            }
        }

        return 0;
    }

    void insert(const std::vector<int32_t>& data) {
        uint32_t node = 0;
        for (int32_t x : data) {
            ++hits_[node];

            node = follow(node, x);
            if (!node)
                node = create(node, x);
        }

        ++hits_[node];
    }

    int32_t query(const std::vector<int32_t>& data) const {
        uint32_t node = 0;
        for (int32_t x : data) {
            node = follow(node, x);
            if (!node) {
                return 0;
            }
        }

        return hits_[node];
    }
private:
    std::vector<std::vector<std::pair<uint32_t, uint32_t>>> children_;
    std::vector<int32_t> hits_;
};
