#include "RPN.hpp"

RPN::RPN()
{
	//std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN& other) :
	_value(other._value)
{
	//std::cout << "Copy constructor called" << std::endl;
}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_value = other._value;
	//std::cout << "Assigment operator called" << std::endl;
	return *this;
}

RPN::~RPN()
{
	//std::cout << "Destructor called" << std::endl;
}

const char* RPN::ErrorException::what() const throw()
{
	return "Error";
}

int RPN::count(int left, int right, std::string data)
{
	switch (data[0])
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		if (right == 0)
			throw ErrorException();
		return left / right;
	default:
		throw ErrorException();
	}

	//if (data[0] == '+')
	//	return left + right;
	//if (data[0] == '-')
	//	return left - right;
	//if (data[0] == '*')
	//	return left * right;
	//else
	//	return left / right;
	
}

void RPN::loadProcess(const std::string& data)
{
	std::stringstream	ss(data);
	std::string			token;

	while (ss >> token)
	{
		if (token.size() != 1)
			throw ErrorException();

		if (isdigit(token[0]))
		{
			_value.push(token[0] - '0');
			continue ;
		}

		if (token[0] == '+'	|| token[0] == '-'
			|| token[0] == '*' || token[0] == '/')
		{
			if (_value.size() < 2)
				throw ErrorException();
			int	right = _value.top();
			_value.pop();
			int	left = _value.top();
			_value.pop();
			_value.push(count(left, right, token));
		}
		else
			throw ErrorException();
	}
	if (_value.size() != 1)
		throw ErrorException();
	std::cout << _value.top() << std::endl;


	//std::string	num = data;

	//for (int i = 0; data[i]; i++)
	//{
	//	if (data[i] == ' ')
	//		continue ;
	//	if (data[i] >= '0' && data[i] <= '9')
	//	{
	//		_value.push(data[i] - '0');
	//		continue ;
	//	}
	//	if (data[i] == '+' || data[i] == '-'
	//		|| data[i] == '*' || data[i] == '/')
	//	{
	//		int m = _value.top();
	//		_value.pop();
	//		int j = _value.top();
	//		_value.pop();
	//		_value.push(count(j, m, data, i));
	//		continue ;
	//	}
	//	else
	//		throw ErrorException();
	//}
	//std::cout << _value.top() << std::endl;
}
