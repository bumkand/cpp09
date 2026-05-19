#ifndef RPN_HPP
#define RPN_HPP

#include <cstdlib>
#include <iostream>
#include <stack>
#include <exception>
#include <sstream>

class RPN
{
	private:
		std::stack<int>	_value;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
		class ErrorException : public std::exception
		{
			const char* what() const throw();
		};

		int count(int left, int right, std::string data);
		void loadProcess(const std::string& data);
};


#endif