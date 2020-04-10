// src: kactl
struct RMQ {
    using T = int;
    T f(T a, T b) {
        return min(a, b);
    }

	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
            for (int j = 0; j < jmp[k].size(); ++j) {
				jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
            }
		}
	}

    // [a, b)
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
