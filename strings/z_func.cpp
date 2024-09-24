// z_func: z[i] is the LCP of s[0:] and s[i:]. z[0] is undefined.
// source: kactl?
template<typename T> 
std::vector<int32_t> z_func(const T& s) {
    int32_t n = s.size();
    std::vector<int32_t> z(n);
    for (int32_t i = 1, l, r = -1; i < n; ++i) {
        z[i] = r > i ? std::min(r - i, z[i - l]) : 0;
        while (i + z[i] < n && s[i + z[i]] == s[z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }

    return z;
};
