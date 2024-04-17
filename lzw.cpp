#include "lzw.h"
#include <unordered_map>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

std::vector<int> compress(const std::string& inStr) {
    std::stringstream in(inStr);
    vector<int> res;
    unordered_map<string, unsigned> table;

    for (int i = 0; i < 256; i++)
        table[{char(i)}] = i;

    string x = { (char)in.get() };
    char y;
    if (in)
        while (in.peek() != EOF)
        {
            y = in.get();
            string xy = x + y;
            if (table.find(xy) != table.end())
                x = xy;
            else
            {
                res.push_back(table[x]);
                table[xy] = table.size();
                x = { y };
            }
        }

    res.push_back(table[x]);


    return res;
}

std::string decompress(const std::vector<int>& vec) {
    std::ostringstream out;
    unordered_map<unsigned, string> table;


    for (int i = 0; i < 256; i++)
        table[i] = { char(i) };

    string x;
    int y = vec[0];
    auto iter = vec.begin() + 1;

    x = table[y];
    while (iter != vec.end())
    {
        y = *(iter++);

        string yValue;

        if (y < table.size())
            yValue = table[y];
        else
            yValue = { x[0] };

        string xy = x + yValue[0];
        out << x;
        table[table.size()] = xy;
        x = yValue;
    }

    out << x;

    return out.str();
}
