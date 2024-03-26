#include "sundaram.h"

std::vector<int> sieve(int n) {
    std::vector<int> primes;
    int N = (n+1)/2-1;
    std::vector<bool> v(N, true);
    for (unsigned i = 1; 2 * i * (1 + i) <= N; i++)
        for (unsigned j = i; i + j + 2 * i * j <= N; j++)
            v[i+j+2*i*j - 1] = false;

    for (unsigned i = 0; i < N; i++)
        if (v[i])
            primes.push_back(2*i + 3);
    return primes;
}
