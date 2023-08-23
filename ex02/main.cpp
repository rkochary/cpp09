#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout  << "Error: invalid arguments\n";
        return (2);
    }
    PmergeMe sort;
    sort.sorting(argc, argv);
    return 0;
}