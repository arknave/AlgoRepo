// return {x, y, g} such that ax + by = g and g is the gcd of x and y
std::array<int64_t, 3> euclid(int64_t a, int64_t b) {
    int64_t s1 = 1, s2 = 0;
    int64_t t1 = 0, t2 = 1;
    int64_t r1 = a, r2 = b;
    while (r2 != 0) {
        int64_t q = r1 / r2;
        s1 = std::exchange(s2, s1 - q * s2);
        t1 = std::exchange(t2, t1 - q * t2);
        r1 = std::exchange(r2, r1 % r2);
    }
    
    assert(s1 * a + t1 * b == r1);
    return {s1, t1, r1};
}

int64_t inverse(int64_t a, int64_t m) {
    auto [x, y, g] = euclid(a, m);
    if (g != 1) {
        // fail somehow
        return -1;
    }

    x %= m;
    if (x < 0) {
        x += m;
    }

    return x;
}
