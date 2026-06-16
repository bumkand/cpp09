#include "PmergeMe.hpp"

PmergeMe::PmergeMe() :
	_v(0),
	_d(0),
	_countVec(0),
	_countDeq(0)
{
	//std::cout << "Default constructor called" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other) :
	_v(other._v),
	_d(other._d),
	_countVec(other._countVec),
	_countDeq(other._countDeq)
{
	//std::cout << "Copy constructor called" << std::endl;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_v = other._v;
		_d = other._d;
		_countVec = other._countVec;
		_countDeq = other._countDeq;
	}
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

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

void	isSorted(std::vector<int> v)
{
	for (size_t i = 0; i < (v.size() - 1); i++)
	{
		size_t j = i + 1;
		if (v[i] > v[j])
		{
			std::cout << "Not sorted" << std::endl;
			return ;
		}
	}
	std::cout << "Sorted" << std::endl;
}

void PmergeMe::execute(int arc, char* arv[])
{
	try
	{
		checkArv(arc, arv);
		fillCont(arc, arv);

		// Sort Vector and Print Time
		timeval	tim;
		gettimeofday(&tim, NULL);
		double	t1 = (tim.tv_sec * 1000000) + tim.tv_usec;

		_v = fjRecurVec(_v);

		gettimeofday(&tim, NULL);
		double	t2 = (tim.tv_sec * 1000000) + tim.tv_usec;

		std::cout << "After:	";
		for (size_t i = 0; i < _v.size(); i++)
		{
			if (i == 5)
			{
				std::cout << "[...]";
				break ;
			}
			std::cout << _v[i] << " ";
		}
		std::cout << std::endl;
		std::cout << "Time to process a range of 5 elements with std::vector<int> :	" << t2 - t1 << " us" << std::endl;

		isSorted(_v);
		int max = F(_v.size());
		std::cout << "Maximum comparisms: " << max << std::endl;

		std::cout << "Vector counter: " << _countVec << std::endl;

		// Sort Deque and Print Time
		gettimeofday(&tim, NULL);
		t1 = (tim.tv_sec * 1000000) + tim.tv_usec;

		_d = fjRecurDeq(_d);

		gettimeofday(&tim, NULL);
		t2 = (tim.tv_sec * 1000000) + tim.tv_usec;

		std::cout << "Time to process a range of 5 elements with std::deque<int> :	" << t2 - t1 << " us" << std::endl;

		std::cout << "Deque counter: " << _countDeq << std::endl;
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
		_d.push_back(val);
	}
	std::cout << "Before:	";
	for (int i = 0; i < (arc - 1); i++)
	{
		if (i == 5)
		{
			std::cout << "[...]";
			break ;
		}
		std::cout << _v[i] << " ";
	}
	std::cout << std::endl;
}



bool PmergeMe::hasStrugglerVec(std::vector<int> input)
{
	if ((input.size() % 2) != 0)
		return true;
	return false;
}

std::vector<int>::iterator PmergeMe::findLowerBoundVec(std::vector<int>::iterator first, std::vector<int>::iterator last, int val)
{

	while (first != last)
	{
		int mid_range = std::distance(first, last) / 2;
		std::vector<int>::iterator	mid = first + mid_range;
		_countVec++;
		if (*mid < val)
			first = mid + 1;
		else
			last = mid;
	}
	return first;
}

std::vector<int> PmergeMe::fjRecurVec(std::vector<int> input)
{
	if (input.size() < 2)
		return input;
	int struggler = -1;
	if (hasStrugglerVec(input) == true)
	{
		struggler = input[input.size() - 1];
		input.pop_back();
	}
	std::vector<std::pair<int, int> >	pair;
	for (size_t i = 0; i < (input.size() - 1); i += 2)
	{
		if (input[i] < input[i + 1])
		{
			pair.push_back(std::make_pair(input[i], input[i + 1]));
			_countVec++;
		}
		else
		{
			pair.push_back(std::make_pair(input[i + 1], input[i]));
			_countVec++;
		}
	}
	std::vector<int> big;
	for (size_t i = 0; i < pair.size(); i++)
		big.push_back(pair[i].second);

	std::vector<int> mainChain = fjRecurVec(big);

	std::vector<std::pair<int, int> >	pend;
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		size_t j = 0;
		while (mainChain[i] != pair[j].second)
			j++;
		pend.push_back(std::make_pair(pair[j].first, pair[j].second));
		if ((i + 1) == mainChain.size() && struggler >= 0)
			pend.push_back(std::make_pair(struggler, struggler));
	}

	std::vector<int>	n = jacobNumVec(pend.size());

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector<int>::iterator	it;
		if (pend[n[i]].first != pend[n[i]].second)
		{
			it = std::find(mainChain.begin(), mainChain.end(), pend[n[i]].second);
			it = findLowerBoundVec(mainChain.begin(), it, pend[n[i]].first);
			mainChain.insert(it, pend[n[i]].first);
		}
		else
		{
			it = findLowerBoundVec(mainChain.begin(), mainChain.end(), struggler);
			mainChain.insert(it, struggler);
		}
	}
	
	return mainChain;
}

std::vector<int> PmergeMe::jacobNumVec(size_t num)
{
	std::vector<int>	vec;
	size_t	curr = 1;
	size_t	prev = 0;
	size_t	next = 0;

	while (next < num)
	{
		for (size_t i = curr; i > prev; i--)
			vec.push_back(i - 1);
		next = curr + (2 * prev);
		prev = curr;
		curr = next;
	}
	if (next >= num)
	{
		for (size_t i = num; i > prev; i--)
			vec.push_back(i - 1);
	}
	return vec;
}



bool PmergeMe::hasStrugglerDeq(std::deque<int> input)
{
	if ((input.size() % 2) != 0)
		return true;
	return false;
}

std::deque<int>::iterator PmergeMe::findLowerBoundDeq(std::deque<int>::iterator first, std::deque<int>::iterator last, int val)
{

	while (first != last)
	{
		int mid_range = std::distance(first, last) / 2;
		std::deque<int>::iterator	mid = first + mid_range;
		_countDeq++;
		if (*mid < val)
			first = mid + 1;
		else
			last = mid;
	}
	return first;
}

std::deque<int> PmergeMe::fjRecurDeq(std::deque<int> input)
{
	if (input.size() < 2)
		return input;
	int struggler = -1;
	if (hasStrugglerDeq(input) == true)
	{
		struggler = input[input.size() - 1];
		input.pop_back();
	}
	std::deque<std::pair<int, int> >	pair;
	for (size_t i = 0; i < (input.size() - 1); i += 2)
	{
		if (input[i] < input[i + 1])
		{
			pair.push_back(std::make_pair(input[i], input[i + 1]));
			_countDeq++;
		}
		else
		{
			pair.push_back(std::make_pair(input[i + 1], input[i]));
			_countDeq++;
		}
	}
	std::deque<int> big;
	for (size_t i = 0; i < pair.size(); i++)
		big.push_back(pair[i].second);

	std::deque<int> mainChain = fjRecurDeq(big);

	std::deque<std::pair<int, int> >	pend;
	for (size_t i = 0; i < mainChain.size(); i++)
	{
		size_t j = 0;
		while (mainChain[i] != pair[j].second)
			j++;
		pend.push_back(std::make_pair(pair[j].first, pair[j].second));
		if ((i + 1) == mainChain.size() && struggler >= 0)
			pend.push_back(std::make_pair(struggler, struggler));
	}

	std::deque<int>	n = jacobNumDeq(pend.size());

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::deque<int>::iterator	it;
		if (pend[n[i]].first != pend[n[i]].second)
		{
			it = std::find(mainChain.begin(), mainChain.end(), pend[n[i]].second);
			it = findLowerBoundDeq(mainChain.begin(), it, pend[n[i]].first);
			mainChain.insert(it, pend[n[i]].first);
		}
		else
		{
			it = findLowerBoundDeq(mainChain.begin(), mainChain.end(), struggler);
			mainChain.insert(it, struggler);
		}
	}
	
	return mainChain;
}

std::deque<int> PmergeMe::jacobNumDeq(size_t num)
{
	std::deque<int>	vec;
	size_t	curr = 1;
	size_t	prev = 0;
	size_t	next = 0;

	while (next < num)
	{
		for (size_t i = curr; i > prev; i--)
			vec.push_back(i - 1);
		next = curr + (2 * prev);
		prev = curr;
		curr = next;
	}
	if (next >= num)
	{
		for (size_t i = num; i > prev; i--)
			vec.push_back(i - 1);
	}
	return vec;
}
