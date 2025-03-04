// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HtmlDecode.h"

void HtmlDecode(std::istream &input, std::ostream &output);

int main()
{
	HtmlDecode(std::cin, std::cout);

	return 0;
}


void HtmlDecode(std::istream &input, std::ostream &output)
{
	std::string html;

	while (std::getline(input, html))
	{
		output << HtmlDecode(html) << "\n";
	}
}