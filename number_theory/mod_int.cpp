template <int MOD>
struct modint {
    constexpr static int64_t fix(int64_t x) {
        x %= MOD;
        if (x < 0) x += MOD;
        return x;
    }

    int64_t v;
    constexpr modint(const int64_t _v = 0): v(fix(_v)) {}

    constexpr modint(const modint& other) {
        v = other.v;
    }

    // not generally useful, but good for maps?
    bool operator<(const modint& other) const { return v < other.v; }
    bool operator>(const modint& other) const { return v > other.v; }
    bool operator<=(const modint& other) const { return v <= other.v; }
    bool operator>=(const modint& other) const { return v >= other.v; }
    bool operator==(const modint& other) const { return v == other.v; }
    bool operator!=(const modint& other) const { return v != other.v; }

    modint& operator+=(const modint& other) {
        v += other.v;
        if (v >= MOD)
            v -= MOD;
        return *this;
    }

    modint& operator-=(const modint& other) {
        v -= other.v;
        if (v < 0)
            v += MOD;
        return *this;
    }

    modint& operator*=(const modint& other) {
        v = 1LL * v * other.v % MOD;
        return *this;
    }

    modint& operator/=(const modint& other) {
        *this *= other.inv();
        return *this;
    }

    modint operator+(const modint& other) const {
        return modint(v) += other;
    }

    modint operator-(const modint& other) const {
        return modint(v) -= other;
    }

    modint operator*(const modint& other) const {
        return modint(v) *= other;
    }

    modint operator/(const modint& other) const {
        return modint(v) /= other;
    }

    static modint pow(const modint& b, int64_t e) {
        modint res = 1;
        modint bb = b;
        for (int64_t p = 1; p <= e; p <<= 1) {
            if (e & p) {
                res *= bb;
            }

            bb *= bb;
        }

        return res;
    }

    modint pow(int64_t e) const {
        return pow(*this, e);
    }

    modint inv() const {
        return pow(MOD - 2);
    }

    friend std::istream& operator>>(std::istream& is, modint& m) {
        int64_t x;
        is >> x;

        m.v = fix(x);

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const modint& m) {
        return os << m.v;
    }
};
using mi = modint<1'000'000'007>;
using mi = modint<998'244'353>;

/*
mi fact[MAXN], tcaf[MAXN];

void gen_fact() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    tcaf[MAXN - 1] = mi(1) / fact[MAXN - 1];
    for (int i = MAXN - 2; i >= 0; --i) {
        tcaf[i] = tcaf[i + 1] * (i + 1);
    }
}

mi choose(int n, int k) {
    assert(n >= 0);
    assert(0 <= k and k <= n);

    return fact[n] * tcaf[k] * tcaf[n - k];
}
*/
