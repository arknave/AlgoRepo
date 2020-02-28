struct modint {
    static const int MOD = 1e9 + 7;

    int v;
    modint(const int _v = 0): v(_v % MOD) {
        if (v < 0) v += MOD;
    }

    bool operator==(const modint& other) const {
        return v == other.v;
    }

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

    static modint pow(const modint& b, ll e) {
        if (e == 0) return 1;
        modint x = pow(b * b, e / 2);
        return (e % 2) ? b * x : x;
    }

    modint pow(ll e) const {
        return pow(*this, e);
    }

    modint inv() const {
        return pow(MOD - 2);
    }

    friend ostream& operator<<(ostream& os, modint m) {
        return os << m.v;
    }
};

modint fact[MAXN], tcaf[MAXN];

void gen_fact() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i - 1] * i;
    }

    tcaf[MAXN - 1] = modint(1) / fact[MAXN - 1];
    for (int i = MAXN - 2; i >= 0; --i) {
        tcaf[i] = tcaf[i + 1] * (i + 1);
    }
}

modint choose(int n, int k) {
    assert(n >= 0);
    assert(0 <= k and k <= n);

    return fact[n] * tcaf[k] * tcaf[n - k];
}
