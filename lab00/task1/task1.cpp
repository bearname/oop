// task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	for (int i = 100; i >= 2; i -= 2)
	{
		std::cout << i;
		if (i != 2)
		{
			std::cout << ", ";
		}
	}
	
	std::cout << "\n";

	return 0;
}
