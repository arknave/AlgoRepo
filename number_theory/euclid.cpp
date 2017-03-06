// Finds the inverse of a for any mod
int inv(int a, int mod) {
    int s1 = 1, s2 = 0;
    int t1 = 0, t2 = 1;
    int r1 = a;
    int r2 = mod;
    while (r2 != 0) {
        int q = r1 / r2;
        int ns = s1 - q * s2;
        int nt = t1 - q * t2;
        int nr = r1 % r2;
        s1 = s2;
        t1 = t2;
        r1 = r2;
        
        s2 = ns;
        t2 = nt;
        r2 = nr;
    }
    
    return (s1 + mod) % mod;
}
