#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>

class RPN
{
    public:
        RPN();
        RPN(char *);
        RPN(const RPN &);
        RPN& operator=(const RPN &);
        ~RPN();
        void calculate();

    private:
        std::stack<int> _mainStack;
        std::string _input;
    
    private:
        void fillstacks();
        bool is_operator(std::string::const_iterator );
        bool is_valid_number(std::string::const_iterator );
};

#endif