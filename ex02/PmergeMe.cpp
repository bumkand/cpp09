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

		timeval	tim;
		gettimeofday(&tim, NULL);
		double	t1 = (tim.tv_sec * 1000000) + tim.tv_usec;

		fillCont(arc, arv);
		algo();

		gettimeofday(&tim, NULL);
		double	t2 = (tim.tv_sec * 1000000) + tim.tv_usec;
		std::cout << "Time to process elements in microseconds : " << t2 - t1 << std::endl;
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

void PmergeMe::fillCont(int arc, char* arv[])
{
	for (int i = 1; i < arc; i++)
	{
		std::string s = arv[i];
		std::istringstream ss(s);
		int	val;
		ss >> val;
		_v.push_back(val);
	}
	for (int i = 0; i < (arc - 1); i++)
		std::cout << _v[i] << " ";
	std::cout << std::endl;
}

bool PmergeMe::hasStruggler(std::vector<int> input)
{
	if ((input.size() % 2) != 0)
		return true;
	return false;
}

std::vector<int> PmergeMe::fjRecur(std::vector<int> input)
{
	if (input.size() < 2)
		return input;
	int struggler;
	if (hasStruggler(input) == true)
	{
		struggler = input[input.size() - 1];
		input.pop_back();
	}
	std::vector<std::pair<int, int> >	pair;
	for (int i = 0; i < (input.size() - 1); i += 2)
	{
		if (input[i] < input[i + 1])
			pair.push_back(std::make_pair(input[i], input[i + 1]));
		else
			pair.push_back(std::make_pair(input[i + 1], input[i]));
	}
}

void PmergeMe::algo()
{
	_v = fjRecur(_v);
}