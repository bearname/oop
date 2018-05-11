// wordFrequency.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordFrequency.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	WordFrequency wordFrequency = CountFrequencyWords(std::cin, std::cout);

	PrintWordFrequncy(std::cout, wordFrequency);

	return 0;
}

