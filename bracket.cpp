#include "bracket.h"
#include <stack>

bool isOpeningBracket(char c)
{
    switch (c)
    {
    case '(':
    case '{':
    case '[':
    case '<':
        return true;
    }
    return false;
}

bool isClosingBracket(char c)
{
    switch (c)
    {
    case ')':
    case '}':
    case ']':
    case '>':
        return true;
    }
    return false;
}

char getPair(char c)
{
    switch (c)
    {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    case '>':
        return '<';
    }

    return 0;
}

bool checkBrackets(std::string str)
{
    std::stack<char> s;
    for (char c : str)
    {
        if (isOpeningBracket(c))
            s.push(c);
        else if (isClosingBracket(c))
        {
            if (s.empty() || s.top() != getPair(c))
                return false;
            s.pop();
        }
    }

    return s.empty();
}