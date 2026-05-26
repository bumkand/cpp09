#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdio>
#include <iostream>
#include <vector>

class PmergeMe
{
	private:
		std::vector<int>	_v;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();
};


#endif
