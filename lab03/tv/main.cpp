// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TVSet.h"
#include "TVSetController.h"

int main()
{
	CTVSet tvSet;
	CTVSetController cntrlTVSet(tvSet, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";

		if (!cntrlTVSet.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}
    return 0;
}

