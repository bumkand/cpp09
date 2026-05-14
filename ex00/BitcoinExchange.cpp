#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	//std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) :
	_database(other._database)
{
	//std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
	//std::cout << "Assigment operator called" << std::endl;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "Destructor called" << std::endl;
}

const char* BitcoinExchange::LoadException::what() const throw()
{
	return "Loading data from data.csv failed";
}

void BitcoinExchange::loadData(const std::string& data)
{
	std::ifstream	file(data.c_str());

	if (file.is_open())
	{
		std::string	line;
		std::string	date;
		std::string	num;
		double		value;

		while (std::getline(file, line))
		{
			if (!line.find(','))
				continue ;
			date = line.substr(0, line.find(','));
			num = line.substr(line.find(',') + 1);
			std::stringstream ss(num);
			ss >> value;

			if (date == "date")
				continue ;

			_database[date] = value;

			std::cout << _database[date] << std::endl;
		}
		file.close();
	}
	else
	{
		throw LoadException();
	}
}
