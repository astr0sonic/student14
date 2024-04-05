#include "rpn.h"
#include <sstream>
#include <stack>
#include "rpn.h"
#include <cmath>

using namespace std;

double N2(std::istream& in)
{
    std::stack<double> s;
    while (in.peek() != EOF && in.peek() != '\n')
    {
        char c = in.peek();
        if (isdigit(c))
        {
            double d;
            in >> d;
            s.push(d);
        }
        else
        {
            double a, b;
            in.get();
            switch (c)
            {
            case '+':
                if (s.size() < 2)
                    throw std::invalid_argument("Wrong input");
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                s.push(a + b);
                break;
            case '-':
                if (s.size() < 2)
                    throw std::invalid_argument("Wrong input");
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                s.push(a - b);
                break;
            case '*':
                if (s.size() < 2)
                    throw std::invalid_argument("Wrong input");
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                s.push(a * b);
                break;
            case '/':
                if (s.size() < 2)
                    throw std::invalid_argument("Wrong input");
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                s.push(a / b);
                break;
            case '^':
                if (s.size() < 2)
                    throw std::invalid_argument("Wrong input");
                b = s.top();
                s.pop();
                a = s.top();
                s.pop();
                s.push(pow(a, b));
                break;
            case '~':
                if (s.size() < 1)
                    throw std::invalid_argument("Wrong input");
                a = s.top();
                s.pop();
                s.push(-a);
                break;
            case ' ':
                break;
            default:
                throw std::invalid_argument("Wrong input");
            }
        }
    }
    if (s.size() > 1)
        throw std::invalid_argument("Wrong input");

    return s.top();
}

double calculateRPN(std::string const& str)
{
    std::stringstream in(str, std::ios_base::in);
    return N2(in);
}