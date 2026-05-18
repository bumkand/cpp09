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

int	count(int j, int m, std::string data, int i)
{
	if (data[i] == '+')
		return j + m;
	if (data[i] == '-')
		return j - m;
	if (data[i] == '*')
		return j * m;
	else
		return j / m;
	
}

void RPN::loadProcess(const std::string& data)
{
	std::string	num = data;

	for (int i = 0; data[i]; i++)
	{
		if (data[i] == ' ')
			continue ;
		if (data[i] >= '0' && data[i] <= '9')
		{
			_value.push(data[i] - '0');
			continue ;
		}
		if (data[i] == '+' || data[i] == '-'
			|| data[i] == '*' || data[i] == '/')
		{
			int m = _value.top();
			_value.pop();
			int j = _value.top();
			_value.pop();
			_value.push(count(j, m, data, i));
			continue ;
		}
		else
			throw ErrorException();
	}
	std::cout << _value.top() << std::endl;
}
