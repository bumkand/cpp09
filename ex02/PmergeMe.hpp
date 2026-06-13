#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>
#include <sys/time.h>
#include <bits/stdc++.h>

class PmergeMe
{
	private:
		std::vector<int>	_v;
		std::deque<int>		_d;
		size_t				_countVec;
		size_t				_countDeq;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		class ErrorException : public std::exception
		{
			const char* what() const throw();
		};

		void						execute(int arc, char* arv[]);
		void						checkArv(int arc, char* arv[]);
		void						fillCont(int arc, char* arv[]);

		std::vector<int>			fjRecurVec(std::vector<int> input);
		bool						hasStrugglerVec(std::vector<int> input);
		std::vector<int>			jacobNumVec(size_t num);
		std::vector<int>::iterator	findLowerBound(std::vector<int>::iterator first, std::vector<int>::iterator last, int val);

		std::deque<int>				fjRecurDeq(std::deque<int> input);
		bool						hasStrugglerDeq(std::deque<int> input);
		std::deque<int>				jacobNumDeq(size_t num);
};


#endif
