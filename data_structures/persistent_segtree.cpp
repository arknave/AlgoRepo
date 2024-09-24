// Fully persistent segtree
struct Node {
    static constexpr int64_t INF = 9e18;

    using T = std::array<int64_t, 2>;
    static constexpr T UNIT = {INF, INF};

    T value = UNIT;
    std::array<Node*, 2> children = {nullptr, nullptr};

    static constexpr T op(T a, T b) {
        return std::min(a, b);
    }

    void pull() {
        value = op(children[0]->value, children[1]->value);
    }
};

Node* makeNode() {
    return new Node{};
}

Node* build(const std::vector<int64_t>& a, uint32_t l, uint32_t r) {
    Node* res = makeNode();
    if (l + 1 == r) {
        res->value[0] = a[l];
        res->value[1] = l;
    } else {
        uint32_t m = (l + r) / 2;

        res->children[0] = build(a, l, m);
        res->children[1] = build(a, m, r);
        res->pull();
    }

    return res;
}

Node* update(Node* root, uint32_t tl, uint32_t tr, uint32_t idx, Node::T v) {
    Node* res = makeNode();
    res->value = root->value;
    res->children = root->children;
    if (tl + 1 == tr) {
        res->value = v;
    } else {
        uint32_t m = (tl + tr) / 2;

        if (idx < m) {
            res->children[0] = update(root->children[0], tl, m, idx, v);
        } else {
            res->children[1] = update(root->children[1], m, tr, idx, v);
        }

        res->pull();
    }

    return res;
}

Node::T query(Node* root, uint32_t tl, uint32_t tr, uint32_t ql, uint32_t qr) {
    if (tl >= qr || tr <= ql) {
        return Node::UNIT;
    } else if (ql <= tl && tr <= qr) {
        return root->value;
    } else {
        uint32_t tm = (tl + tr) / 2;

        return Node::op(query(root->children[0], tl, tm, ql, qr), query(root->children[1], tm, tr, ql, qr));
    }
}
