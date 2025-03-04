// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Math.h"

void HandleUserCommand(std::istream &input, std::ostream& output)
{
	double a = 0.0;
	double b = 0.0;
	double c = 0.0;
	double d = 0.0;
	double e = 0.0;

	output << "> ";

	while (input >> a >> b >> c >> d >> e)
	{
		try
		{
			output << Solve4(a, b, c, d, e) << std::endl;
		}
		catch (std::exception const& err)
		{
			std::cout << err.what() << std::endl;
		}
	
		output << "> ";
	}
}

int main()
{
	HandleUserCommand(std::cin, std::cout);

    return 0;
}

