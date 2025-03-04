// task2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

bool StringToInt(const std::string& str, int& result)
{
	try
	{
		result = std::stoi(str);
		return true;
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what() << "\n";
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << e.what() << "\n";
	}

	return false;
}

int SumDigits(int i)
{
	int sum = 0;

	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

void PrintNumbers(std::ostream& output, int upperBound)
{
	for (int i = 0; i < upperBound; ++i)
	{
		int sum = SumDigits(i);

		if ((i % sum) == 0)
		{
			if (i != 1)
			{
				output << ", ";
			}
			output << i;
		}
	}

	output << "\n";
}

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Usage: task2.exe <upper bound>\n";
		return 1;
	}

	int upperBound = 0;
	if (!StringToInt(argv[1], upperBound))
	{
		std::cout << "the upper bound must be greater than or equal to 1\n";

		return 1;
	}

	PrintNumbers(std::cout, upperBound);

	return 0;
}
