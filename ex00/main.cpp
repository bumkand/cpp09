#include "BitcoinExchange.hpp"

int	main(int arc, char* arg[])
{
	if (arc != 2)
		return std::cerr << "Wrong amount of arguments" << std::endl, 1;
	
	BitcoinExchange	ex;

	ex.loadData(arg[1]);
}