#include "RPN.hpp"

int	main(int arc, char* arv[])
{
	if (arc != 2)
	{
		std::cerr << "Error: wrong amount of arguments" << std::endl;
		return 1;
	}

	try
	{
		RPN rpn;
		rpn.loadProcess(arv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}