#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <exception>
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_database;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		class LoadException : public std::exception
		{
			const char* what() const throw();
		};

		class ProcessException : public std::exception
		{
			const char* what() const throw();
		};

		void loadData(const std::string& data);
		void processInput(const std::string& data);
};


#endif