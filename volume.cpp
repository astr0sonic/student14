#include <algorithm>

int getMaxVolume(int a, int b, int c, int n, int* values)
{
    int const* maxStart = values;
    int max = 0;

    for (int const* i = values; i + a < values + n; ++i)
        if (std::min(*i, i[a]) > max && std::min(*i, i[a]) <= c)
        {
            max = std::min({ *i, i[a] });
            maxStart = i;
        }

    auto i1 = maxStart, i2 = maxStart + std::min(a, n - 1);
    max *= a;

    while (i1 != i2)
    {
        if (std::min(*i1, *i2) <= c)
            max = std::max<int>(max, (i2 - i1) * std::min(*i1, *i2));
        if (*i1 == std::min(*i1, *i2))
            i1++;
        else
            i2--;
    }
    return b * max;
}
