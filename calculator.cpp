#include "calculator.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <cmath>

unsigned getPriority(char c)
{
    switch (c)
    {
    case '^':
        return 0;
    case '~':
        return 1;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 3;
    case '(':
        return 4;
    default:
        throw std::invalid_argument("Wrong char");
    }
}

double N3(std::istream &inStr)
{
    unsigned lastBracket = 0;
    std::string str;
    std::getline(inStr, str, '\n');
    std::istringstream in(std::move(str));
    bool state = false; // false -- ожидаем число / ( / унарный минус        true -- ожидаем бинарный оператор / )
    std::stringstream out;
    std::stack<char> s;
    while (in.peek() != EOF && in.peek() != '\n')
    {
        char c = in.peek();
        if (isdigit(c))
        {
            if (state)
                throw std::exception();
                //throw wrongExpression(std::format("Unexpected digit \"{}\" found", c), in.tellg());

            double d;
            in >> d;
            out << d << ' ';
            state = true;
        }
        else
        {
            in.get();
            switch (c)
            {
            case ' ':
                break;

            case '^':
            case '*':
            case '/':
            case '+':
                if (!state)
                    throw std::exception();
                    //throw wrongExpression(std::format("Unexpected operator \"{}\" found", c), in.tellg());

                while (!s.empty() && getPriority(s.top()) <= getPriority(c))
                {
                    out << s.top() << ' ';
                    s.pop();
                }

                s.push(c);
                state = false;
                break;
            case '(':
                if (state)
                    throw std::exception();
                    //throw wrongExpression(std::format("Unexpected \"(\" found"), in.tellg());

                lastBracket = in.tellg();
                s.push(c);
                break;
            case ')':
                if (!state)
                    throw std::exception();
                    //throw wrongExpression(std::format("Unexpected \")\" found"), in.tellg());
                while (!s.empty() && s.top() != '(')
                {
                    out << s.top() << ' ';
                    s.pop();
                }

                if (s.empty())
                    throw std::exception();
                    //throw wrongExpression(std::format("Unmatched \")\" found"), in.tellg());

                s.pop();

                break;

            case '-':
                if (!state)
                    c = '~';

                while (!s.empty() && getPriority(s.top()) <= getPriority(c))
                {
                    out << s.top() << ' ';
                    s.pop();
                }
                s.push(c);
                state = false;

                break;

            default:
                throw std::exception();
                //throw wrongExpression(std::format("Unexpected char \"{}\" found", c), in.tellg());
            }
        }
    }

    if (!state)
        throw std::exception();
        //throw wrongExpression("Operator or \"(\" can't be the last char in an expression", in.str().size());

    while (!s.empty())
    {
        if (s.top() == '(')
            throw std::exception();
            //throw wrongExpression("Unmatched \"(\" found", lastBracket);
        out << s.top() << ' ';
        s.pop();
    }

    //std::cout << out.str() << std::endl;
    return N2(out);
}

double calculate(std::string const& in)
{
    std::stringstream str(in);
    return N3(str);
}

double N2(std::istream &in)
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
                s.push(std::pow(a, b));
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

