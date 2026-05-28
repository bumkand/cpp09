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
	std::string	s;
	long int val;
	std::vector<int>	vec;
	for (int i = 1; arv[i]; i++)
	{
		s = arv[i];
		std::istringstream ss(s);
		
		if (!(ss >> val))
			throw ErrorException();
		std::string leftover;
		if (ss >> leftover)
			throw ErrorException();
		if (val < 0)
			throw ErrorException();
		if (val > std::numeric_limits<int>::max())
			throw ErrorException();
		int valid = static_cast<int>(val);
		if (std::find(vec.begin(), vec.end(), valid) != vec.end())
			throw ErrorException();
		vec.push_back(valid);
	}
}
