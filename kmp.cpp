#include "kmp.h"

std::vector<int> getIndices(const std::string& target, const std::string& str) {
	const size_t sz = target.size();
	std::vector<int> res;
	if (!sz)
		return res;

	size_t* prefix = new size_t[sz];

	size_t j = prefix[0] = 0;
	for (size_t i = 1; i < sz; ++i)
	{
		while (j > 0 && target[j] != target[i])
			j = prefix[j - 1];
		if (target[i] == target[j])
			++j;
		prefix[i] = j;
	}

	j = 0;

	for (size_t i = 0; i < str.size(); ++i)
	{
		while (j > 0 && target[j] != str[i])
			j = prefix[j - 1];
		if (str[i] == target[j])
			++j;

		if (j == sz)
		{
			res.push_back(i - sz + 1);
			j = prefix[j - 1];
		}
	}

	delete[] prefix;
	return res;
}
