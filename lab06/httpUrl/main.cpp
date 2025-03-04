// httpUrl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CUrlParsingError.h"
#include "CHttpUrl.h"

void HandleUserCommand(std::istream& input, std::ostream& output)
{
	std::string commandLine;
	
	output << "> ";

	while (std::getline(input, commandLine))
	{
		try
		{
			CHttpUrl httpUrl(commandLine);

			std::cout << httpUrl << "\n";
		}
		catch (std::exception const& err)
		{
			std::cout << err.what() << "\n";
		}
		catch (...)
		{
			std::cout << "unkown error\n";
		}
		output << "> ";
	}
}

int main()
{
	HandleUserCommand(std::cin, std::cout);
	
	return 0;
}

