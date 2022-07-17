// Finds the inverse of a for any mod given gcd(a, mod) = 1
template <typename T>
T inv(T a, T mod) {
    T s1 = 1, s2 = 0;
    T t1 = 0, t2 = 1;
    T r1 = a;
    T r2 = mod;
    while (r2 != 0) {
        T q = r1 / r2;
        T ns = s1 - q * s2;
        T nt = t1 - q * t2;
        T nr = r1 % r2;
        s1 = s2;
        t1 = t2;
        r1 = r2;
        
        s2 = ns;
        t2 = nt;
        r2 = nr;
    }
    
    return (s1 + mod) % mod;
}
