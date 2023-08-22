#include "RPN.hpp"

RPN::RPN() : _input("unknown"){}

RPN::RPN(char *inp)
{
    std::string input(inp);
    _input = input;
}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN& RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
    {
        _mainStack = rhs._mainStack;
        _input = rhs._input;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::is_valid_number(std::string::const_iterator it)
{
    if (std::isdigit(static_cast<unsigned char>(*it)) && static_cast<int>(*it) < 10)
    {
        std::cout  << "Error : argument will always be less than 10" << std::endl;
        return false;
    }
    if (std::isdigit(static_cast<unsigned char>(*it)))
        return true;
    return false;
}

void RPN::calculate()
{
    if (_input == "unknown")
        std::cout << "Error: have not any parametr\n";
    fillstacks();
}

bool RPN::is_operator(std::string::const_iterator it)
{
    if (*it == '-' || *it == '/' || *it == '*' || *it == '+')
        return true;
    return false;
}

void RPN::fillstacks()
{
    std::string::const_iterator it;
    int res_print;
    for (it = _input.begin(); it != _input.end(); ++it)
    {
        if (std::isspace(static_cast<unsigned char>(*it)))
        {
            continue;
        }
        else if (is_valid_number(it))
        {
            _mainStack.push(*it - '0');
        }
        else if (is_operator(it))
        {
            int val1;
            int val2;
            if (!_mainStack.empty())
            {
                val1 = _mainStack.top();
                _mainStack.pop();
            }
            else
            {
                std::cout << "Error : invalid input!\n" ;
                return ;
            }
            if (!_mainStack.empty())
            {
                val2 = _mainStack.top();
                _mainStack.pop();
            }
            else
            {
                std::cout << "Error : invalid input!\n";
                return ;
            }
            switch (*it)
            {
            case '+':
                _mainStack.push(val2 + val1);
                break;
            case '-':
                _mainStack.push(val2 - val1);
                break;
            case '*':
                _mainStack.push(val2 * val1);
                break;
            case '/':
                _mainStack.push(val2 / val1);
                break;
            }
        }
        else
        {
            std::cout << "Error : invalid number" << std::endl;
            return ;
        }
    }
    if (!_mainStack.empty())
    {
        res_print = _mainStack.top();
        _mainStack.pop();
    }
    else
    {
        std::cout << "Error : invalid input!\n" ;
        return ;
    }
    if (_mainStack.empty())
        std::cout << "Result is: " << res_print << std::endl ;
    else
        std::cout << "Error : invalid input!\n" ;
}
