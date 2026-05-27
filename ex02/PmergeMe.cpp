#include "PmergeMe.hpp"

PmergeMe::PmergeMe() :
	_v(0)
{
	//std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_v(other._v)
{
	//std::cout << "Copy constructor called" << std::endl;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
		_v = other._v;
	//std::cout << "Assigment operator called" << std::endl;
	return *this;
}

PmergeMe::~PmergeMe()
{
	//std::cout << "Destructor called" << std::endl;
}

const char* PmergeMe::ErrorException::what() const throw()
{
	return "Error";
}

void PmergeMe::execute(int arc, char* arv[])
{
	try
	{
		checkArv(arc, arv);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}

void PmergeMe::checkArv(int arc, char* arv[])
{
	if (arc < 2)
		throw ErrorException();
	for (int i = 1; arv[i]; i++)
	{
		int j = 0;
		while (arv[i][j])
		{
			if (!(arv[i][j] >= '0' && arv[i][j] <= '9') || arv[i][j] != '+' || arv[i][j] != '-')
				throw ErrorException();
		}
	}
}