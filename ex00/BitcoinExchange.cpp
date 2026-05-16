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
	return "Error: could not open file";
}

const char* BitcoinExchange::ProcessException::what() const throw()
{
	return "Error: could not open file";
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
			if (line.find(',') == std::string::npos)
				continue ;
			date = line.substr(0, line.find(','));
			std::stringstream sd(date);
			sd >> date;
			num = line.substr(line.find(',') + 1);
			std::stringstream sn(num);
			sn >> value;

			if (date == "date")
				continue ;

			_database[date] = value;
		}
		file.close();
	}
	else
	{
		throw LoadException();
	}
}

bool	checkDate(std::string date)
{
	std::stringstream	sd(date);
	sd >> date;
	if (date == "date")
		return false;
	if (date.length() != 10)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	for (int i = 0; i < 10; i++)
	{
		if ((i == 4 || i == 7) && date[i] == '-')
			continue ;
		if (date[i] < '0' || date[i] > '9')
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return false;
		}
	}
	std::stringstream	ss(date);
	int			year;
	int			month;
	int			day;
	ss >> year;
	ss >> month;
	month *= -1;
	ss >> day;
	day *= -1;

	if (year < 2009 || (year == 2009 && month == 1 && day == 1))
	{
		std::cout << "Error: Date is too early to be in database => " << date << std::endl;
		return false;
	}
	if (month > 12)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	if ((month == 1 || month == 3 || month == 5 || month == 7
		|| month == 8 || month == 10 || month == 12) && day > 31)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}
	if (month == 2 && (((year % 4 == 0) && day > 29) || ((year % 4 != 0) && day > 28)))
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return false;
	}

	return true;
}

bool	checkValue(double value)
{
	if (value < 0)
	{
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	if (value > 1000)
	{
		std::cout << "Error: too large number." << std::endl;
		return false;
	}

	return true;
}

void BitcoinExchange::processInput(const std::string& data)
{
	std::ifstream	file(data.c_str());

	if (file.is_open())
	{
		std::string	line;
		std::string	date;
		std::string	num;
		double		value;

		while (getline(file, line))
		{
			if (line.empty() || line.find('|') == std::string::npos)
			{
				if (!line.empty())
					std::cout << "Error: bad input => " << line << std::endl;
				continue ;
			}
			date = line.substr(0, line.find('|'));
			if (checkDate(date) == false)
				continue ;
			std::stringstream sd(date);
			sd >> date;
			
			num = line.substr(line.find('|') + 1);
			std::stringstream	sn(num);
			sn >> value;
			if (checkValue(value) == false)
				continue ;

			std::map<std::string, double>::iterator	it = _database.find(date);

			if (it != _database.end())
			{
				std::cout << it->first << " => " << value << " = " << value * it->second << std::endl;
			}
			else
			{
				it = _database.lower_bound(date);
				it--;
				std::cout << it->first << " => " << value << " = " << value * it->second << std::endl;
			}
		}
		file.close();
	}
	else
		throw ProcessException();
}
