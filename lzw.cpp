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
    map<unsigned, string> table;


    for (int i = 0; i < 256; i++)
        table[i] = { char(i) };

    string x;
    int y = vec[0];
    auto iter = vec.begin() + 1;

    x = table[y];
    out << x;
    while (iter != vec.end())
    {
        y = *(iter++);

        string yValue;

        if (y < table.size())
        {
            yValue = table[y];
            out << yValue;
            string xy = x + yValue[0];
            table[table.size()] = xy;
            x = yValue;
        }
        else
        {
            string xy = x + x[0];
            table[table.size()] = xy;
            out << xy;
            x = xy;
        }
    }

    return out.str();
}
