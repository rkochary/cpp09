#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs)
{
	if (this != &rhs)
	{
		_vect = rhs._vect;
		_deque = rhs._deque;
		_time = rhs._time;
		_t_vector_start = rhs._t_vector_start;
		_t_vector_finish = rhs._t_vector_finish;
		_t_deque_start = rhs._t_deque_start;
		_t_deque_finish = rhs._t_deque_finish;
	}
	return (*this);
}

PmergeMe::~PmergeMe(){}

void PmergeMe::sorting(int argc, char **argv)
{
	std::cout << "Before: " ;
	print_unsorted(argc, argv);
	std::cout << std::endl;

	// for vector
	_t_vector_start = get_current_time(&_time);
	fill_vector(argc, argv);
	mergeSort(_vect, 0, _vect.size() - 1);
	_t_vector_finish = get_current_time(&_time);


	//for deque
	_t_deque_start = get_current_time(&_time);
	fill_deque(argc, argv);
	mergeSort(_deque, 0, _deque.size() - 1);
	_t_deque_finish = get_current_time(&_time);

	std::cout << "After: " ;
	print_sorted();
	std::cout << std::endl;

	std::cout << "Time to process a range of " << argc << " elements with std::vector : " << (_t_vector_finish - _t_vector_start) / 1000 << " us\n";
	std::cout << "Time to process a range of " << argc << " elements with std::deque : " << (_t_deque_finish - _t_deque_start) / 1000 << " us\n";
}
bool PmergeMe::areAllDigits(const std::string& str)
{
	std::string::const_iterator it = str.begin();
	if (*it == '+')
		++it;
	for (; it != str.end(); ++it)
	{
		if (!isdigit(*it)) {
			return false;
		}
	}
	return true;
}

int PmergeMe::check_num(char *num)
{
	int res = -1;
	std::string str(num);
	std::string str1(num);
	std::istringstream stream(str);
	std::istringstream stream1(str);

	std::getline(stream, str, ' ');
	std::istringstream convert(str);
	convert >> res;
	if (stream.fail() || (res == 0 && str[0] != '0') || !areAllDigits(str))
		return -1;
	if (stream.fail())
	{
		return -1;
	}
	return res;
}

void PmergeMe::fill_deque(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		int tmp = check_num(argv[i]);
		if (tmp < 0)
		{
			std::cout << "Error : invalid input!\n" ;
			exit(1);
		}   
		else 
		{
			_deque.push_back(tmp);
		}
	}
}

void PmergeMe::fill_vector(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		int tmp = check_num(argv[i]);
		if (tmp < 0)
		{
			std::cout << "Error : invalid input!\n";
			exit(1);
		}   
		else 
		{
			_vect.push_back(tmp);
		}
	}
}

void PmergeMe::print_unsorted(int argc, char **argv)
{
    if (argc > NUMBER_COUNT)
    {
	    for (int i = 1; i < NUMBER_COUNT; ++i)
	    {
	    	std::cout << argv[i] << " ";
	    }
        std::cout << "[...]";
    }
    else
    {
	    for (int i = 1; i < argc; ++i)
	    {
	    	std::cout << argv[i] << " ";
	    }
    }
}

void PmergeMe::print_sorted()
{
    if (_vect.size() > NUMBER_COUNT)
    {
        std::vector<int>::const_iterator it;
	    for (it = _vect.begin(); it < _vect.begin() + NUMBER_COUNT - 1; ++it)
        {
	    	std::cout << *it << " ";
	    }
        std::cout << "[...]";
    }
    else
    {
	    for (std::vector<int>::const_iterator it = _vect.begin(); it != _vect.end(); ++it)
        {
	    	std::cout << *it << " ";
	    }
    }
}

double	PmergeMe::get_current_time(struct timeval *time)
{
	gettimeofday(time, NULL);
	return ((time->tv_sec * 1000000) + (time->tv_usec));
}
