// more cribbing from KACTL
struct Line {
	mutable int64_t k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(int64_t x) const { return p < x; }

    int64_t operator()(int64_t x) const {
        return k * x + m;
    }
};

std::ostream& operator<<(std::ostream& os, Line l) {
    return os << l.k << "x + " << l.m;
}

struct LineContainer : std::multiset<Line, std::less<>> {
	// (for doubles, use INF = 1/.0, div(a,b) = a/b)
	static const int64_t INF = std::numeric_limits<int64_t>::max();
	int64_t div(int64_t a, int64_t b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->k == y->k) x->p = x->m > y->m ? INF : -INF;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(int64_t k, int64_t m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
    // returns the maximum for all lines
	Line query(int64_t x) {
		assert(!empty());
		return *lower_bound(x);
	}
};
