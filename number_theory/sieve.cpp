#include <iostream>
#include <cmath>
#define MAX_N 1000000

bool sieve[MAX_N]; // 1 if prime, 0 if composite

void genSieve() {
    // Sieve of Eratosthenes - Finds all primes less than a certain value
    // Runtime: O(n loglog n)
    sieve[0] = 0; 
    sieve[1] = 0;
    sieve[2] = 1;
    for(int i=3;i<MAX_N;i+=2) {
        sieve[i] = 1;
    }
    int realCap = (int)ceil(sqrt(MAX_N));
    for(int i=3;i<realCap;i+=2) {
        if(!sieve[i]) continue;
        for(int j=i*i;j<MAX_N;j+=i) {
            sieve[j] = 0;
        }
    }
}

int main() {
    genSieve();
    for(int i=2;i<MAX_N;i++) {
        if(sieve[i]) {
            std::cout << i << '\n';
        }
    }
    return 0;
}
