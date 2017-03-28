#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Burnside's lemma lets you count the number of objects that are distinct
 * under some set of transformations (rotation, reflection, etc)
 * 
 * It works by taking the average of the number of values that are fixed under
 * each operation. Note that the identity counts as an operation!
 * 
 * For this problem, we count the number of necklaces of length n where each
 * segment can have 1 of k colors. The operations are rotate by 0, rotate
 * by 1, rotate by 2, ... rotate by n - 1. Rotating by n is equivalent to
 * rotating by 0, so we have a finite number of actions.
 * 
 * If there are no rotations, there are k^n ways to generate a necklace.
 * In general, if you rotate by x, there are k^gcd(n, x) ways to have a necklace
 * that doesn't change under rotation. I discovered this value by inspection,
 * no proof yet :(
 * 
 * Thus the answer for this particular problem is 1 / n * (k^n + k^1 + 
 *   k^gcd(n, 2) + ... + k^gcd(n, n - 1))
 */

const int MOD = 1000000007;
int n, k;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

inline int sum(const int& a, const int& b) {
    int c = a + b;
    if (c >= MOD) {
        c -= MOD;
    }

    return c;
}

inline int prod(const int& a, const int& b) {
    return (1LL * a * b) % MOD;
}

int modpow(int base, int exp) {
    int res = 1;
    int cur = base;
    for (int p = 1; p <= exp; p <<= 1) {
        if (p & exp) {
            res = prod(res, cur);
        }

        cur = prod(cur, cur);
    }

    return res;
}

int main() {
    scanf("%d %d", &n, &k);
    
    int ans = modpow(k, n);
    for (int x = 1; x < n; ++x) {
        ans = sum(ans, modpow(k, gcd(n, x)));
    }
    
    ans = prod(ans, modpow(n, MOD - 2));
    
    printf("%d\n", ans);
    return 0;
}
