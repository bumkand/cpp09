#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int>	_v;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		class ErrorException : public std::exception
		{
			const char* what() const throw();
		};

		void	execute(int arc, char* arv[]);
		void	checkArv(int arc, char* arv[]);
};


#endif
