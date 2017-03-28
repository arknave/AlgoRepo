inline int sum(const int& a, const int& b, const int& mod) {
    int c = a + b;
    if (c >= mod) {
        c -= mod;
    }

    return c;
}

inline int prod(const int& a, const int& b, const int& mod) {
    return (1LL * a * b) % mod;
}

int modpow(int base, int exp, int mod) {
    int res = 1;
    int cur = base;
    for (int p = 1; p <= exp; p <<= 1) {
        if (p & exp) {
            res = prod(res, cur, mod);
        }

        cur = prod(cur, cur, mod);
    }

    return res;
}

