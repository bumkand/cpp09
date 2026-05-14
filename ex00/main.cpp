#include "BitcoinExchange.hpp"

int	main(int arc, char* arg[])
{
	(void) arg;
	if (arc != 2)
		return std::cerr << "Wrong amount of arguments" << std::endl, 1;
	
	BitcoinExchange	ex;

	try
	{
		ex.loadData("data.csv");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}