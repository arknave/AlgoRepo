#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXN = 1000006;
bool sieve[MAXN]; // 1 if prime, 0 if composite

void gen_sieve() {
    // Sieve of Eratosthenes - Finds all primes less than a certain value
    // Runtime: O(n loglog n)
    memset(sieve, 0, sizeof(sieve));
    sieve[2] = 1;
    for (int i = 3; i < MAXN; i += 2) {
        sieve[i] = 1;
    }

    for (int i = 3; 1LL * i * i <= MAXN; i += 2) {
        if (!sieve[i]) continue;

        for (long long j = 1LL * i * i; j < MAXN; j += 2LL * i) {
            sieve[j] = 0;
        }
    }
}

int main() {
    gen_sieve();
    for (int i = 2; i < MAXN; i++) {
        if (sieve[i]) {
            printf("%d\n", i);
        }
    }

    return 0;
}
