// what is the range of q where
// kq + r = n and r < k and r < q

// kq + r = n
// kq = (n - r)
// q = (n - r) / k
// r can range from 0 to k - 1
// this gives a range for q
// cap the q range also

ll l = n / (k + 1) + 1;
ll r = (n + k) / k;
