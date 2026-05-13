#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) :
	_database(other._database)
{
	std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
	std::cout << "Assigment operator called" << std::endl;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "Destructor called" << std::endl;
}

void BitcoinExchange::loadData(const std::string& data)
{
	std::ifstream	file(data.c_str());

	if (file.is_open())
	{
		std::string	line;
		while (std::getline(file, line))
		{
			std::cout << line << std::endl;
		}
		file.close();
	}
	else
	{
		throw std::exception();
	}
}