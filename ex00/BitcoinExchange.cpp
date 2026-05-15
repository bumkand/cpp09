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

const char* BitcoinExchange::ProcessException::what() const throw()
{
	return "Problem with processing input file";
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
			num = line.substr(line.find(',') + 1);
			std::stringstream ss(num);
			ss >> value;

			if (date == "date")
				continue ;

			_database[date] = value;
		}
		file.close();

		// ------ Print Map Container ------

		//std::map<std::string, double>::iterator	it_beg = _database.begin();
		//std::map<std::string, double>::iterator it_end = _database.end();
		//while (it_beg != it_end)
		//{
		//	std::cout << it_beg->first << " | " << it_beg->second << std::endl;
		//	++it_beg;
		//}

	}
	else
	{
		throw LoadException();
	}
}

int	checkDate(std::string date)
{
	std::stringstream	sd(date);
	sd >> date;
	if (date == "date")
		return 1;
	if (date.length() != 10)
	{
		std::cout << "Error: bad input => " << date << std::endl;
		return 1;
	}
	

	return 0;
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
			if (line.find('|') == std::string::npos)
				continue ;
			
			date = line.substr(0, line.find('|'));
			if (checkDate(date))
				continue ;
			
			num = line.substr(line.find('|') + 1);

			std::stringstream	sn(num);
			sn >> value;

			std::cout << date << " | " << value << std::endl;
			
		}
		file.close();
	}
	else
		throw ProcessException();
}

