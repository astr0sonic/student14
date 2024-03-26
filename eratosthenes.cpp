#include "eratosthenes.h"
#include <vector>

std::vector<int> sieve(int n) {
    std::vector<int> res;
    std::vector<bool> v(n-1, true);
    for (unsigned p = 2; p*p <= n; ++p)
    {
        if (v[p-2])
            for (unsigned i = p*p; i <= n; i+=p)
                v[i-2] = false;
    }

    for (unsigned i = 0; i < n-1; i++)
        if (v[i])
            res.push_back(i + 2);
}
