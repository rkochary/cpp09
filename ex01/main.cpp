#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout <<"Error: takes one parameter\n";
        return (2);
    }
    RPN cal(argv[1]);
    cal.calculate();
}