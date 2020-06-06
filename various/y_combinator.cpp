// From http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
// Tested on https://open.kattis.com/problems/excavatorexpedition

namespace std {
    template<class Fun>
    class y_combinator_result {
        Fun fun_;
        public:
        template<class T>
            explicit y_combinator_result(T&& fun): fun_(std::forward<T>(fun)) {}

        template<class ...Args>
        decltype(auto) operator()(Args&&... args) {
            return fun_(std::ref(*this), std::forward<Args>(args)...);
        }
    };

    template<class Fun>
    decltype(auto) y_combinator(Fun&& fun) {
        return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
    }
} // namespace std

// Usage
std::y_combinator([&](auto self, int u, int p) -> int {
    sz[u] = 1;
    for (int v : graph[u]) {
        if (v == p) continue;
        sz[u] += self(v, u);
    }

    return sz[u];
});
