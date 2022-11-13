// src: kactl
struct RMQ {
    using T = int64_t;
    T f(T a, T b) {
        return std::min(a, b);
    }

    std::vector<std::vector<T>> jmp;
    RMQ(const std::vector<T>& V) : jmp(1, V) {
        for (size_t pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
            jmp.emplace_back(V.size() - pw * 2 + 1);
            for (size_t j = 0; j < jmp[k].size(); ++j) {
                jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
        }
    }

    // [a, b)
    T query(int a, int b) {
        assert(a < b); // or return inf if a >= b
        int32_t dep = 31 - __builtin_clz(b - a);
        return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
    }
};
