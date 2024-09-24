// A treap is a balanced binary search tree, where each node has a priority
// The tree structure is a standard BST, but the nodes must also be a heap keyed by priority
// To allow calling methods on null pointers, this implementation uses free functions on Node*
//
// This version does not satisfy the BST property - it assumes that the treaps
// passed into merge are already sorted.

namespace Lehmer {
    __uint128_t lehmer64_state{0xd34db33f};

    uint64_t next() {
        lehmer64_state *= 0xda942042e4dd58b5;
        return lehmer64_state >> 64;
    }
}

namespace Treap {
    struct Node {
        std::array<Node*, 2> children{};
        int64_t priority{0};

        int64_t val{};

        // aggregate parameters
        int64_t size{1};

        // lazy parameters
        bool isReversed{false};
    };

    std::deque<Node> treapNodes;

    Node* newNode() {
        treapNodes.push_back({});
        treapNodes.back().priority = Lehmer::next();
        return treapNodes.back();
    }

    int64_t getSize(const Node* node) {
        return node ? node->size : 0;
    }

    // Must be O(1). Pushes lazy data down to children
    void push(Node& node) {
        if (node.isReversed) {
            std::swap(node.children[0], node.children[1]);
            node.isReversed = false;
            for (Node* child : node.childen) {
                if (child) child->isReversed ^= 1;
            }
        }
    }

    // Must be O(1). Recomputes aggregate stats of the subtree.
    void pull(Node& node) {
        node.size = 1;
        for (Node* child : node.children) {
            node.size += getSize(child);
        }
    }

    // Split a treap into two: the first will have size leftSize.
    std::array<Node*, 2> split(Node* root, int64_t leftSize) {
        assert(leftSize <= getSize(root));
        if (leftSize == 0) {
            return {nullptr, root};
        }

        assert(root != nullptr);
        push(*root);
        if (leftSize <= getSize(root->children[0])) {
            auto [lhs, rhs] = split(root->children[0], leftSize);
            root->children[0] = rhs;
            pull(*root);

            return {lhs, root};
        } else {
            auto [lhs, rhs] = split(root->children[1], leftSize - 1 - getSize(root->children[0]));
            root->children[1] = lhs;
            pull(*root);

            return {root, rhs};
        }
    }

    // Returns lhs + rhs in one treap.
    Node* merge(Node* lhs, Node* rhs) {
        if (lhs == nullptr) {
            return rhs;
        } else if (rhs == nullptr) {
            return lhs;
        }

        push(*lhs);
        push(*rhs);
        if (lhs->priority > rhs->priority) {
            lhs->children[1] = merge(lhs->children[1], rhs);
            pull(*lhs);

            return lhs;
        } else {
            rhs->children[0] = merge(lhs, rhs->children[0]);
            pull(*rhs);

            return rhs;
        }
    }

    template <typename F>
    auto build(int32_t l, int32_t r, F&& f) -> Node* {
        if (l + 1 == r) {
            return f(l);
        }
        int32_t mid = (l + r) / 2;
        Node* lhs = build(l, mid, f);
        Node* rhs = build(mid, r, f);

        return merge(lhs, rhs);
    }

    template <typename F>
    auto inOrder(Node* root, F&& f) {
        if (root == nullptr) return;
        push(*root);
        inOrder(root->children[0], f);
        f(root);
        inOrder(root->children[1], f);
    }
} // namespace Treap
