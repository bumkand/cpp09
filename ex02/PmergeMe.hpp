#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <exception>
#include <sstream>
#include <limits>
#include <algorithm>
#include <sys/time.h>

class PmergeMe
{
	private:
		std::vector<int>	_v;
		std::vector<int>	fjRecur(std::vector<int> input);

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
		void	fillCont(int arc, char* arv[]);
		void	algo();
		bool	hasStruggler(std::vector<int> input);
		std::vector<size_t>	jacobNum(size_t num);
};


#endif
