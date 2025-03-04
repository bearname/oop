// labyrinth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WaveAlgorithm.h"


void PrintUserHelp(std::ostream &output);
bool WaveAlgorithm(const std::string &inputFileName, const std::string &outputFileName);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "The invalid number of the arguments.\n";
		PrintUserHelp(std::cout);

		return 1;
	}

	if (!WaveAlgorithm(argv[1], argv[2]))
	{
		return 1;
	}

	return 0;
}

void PrintUserHelp(std::ostream &output)
{
	output << "Usage: labyrinth.exe <input file> <output file>\n";
}

bool ReadLabyrinth(const std::string &inputFileName, Labyrinth &labyrinth)
{
	std::ifstream inputFile(inputFileName);

	if (!inputFile.is_open())
	{
		std::cout << "Failed open \"" << inputFileName << "\" for reading." << "\n";
		PrintUserHelp(std::cout);
		return false;
	}

	ErrorType errorType = ReadLabyrinth(inputFile, labyrinth);

	if (errorType != ErrorType::None)
	{
		std::cout << GetErrorMessage(errorType) << "\n";
		return false;
	}

	return true;
}

bool PrintLabyrinth(const std::string &outputFileName, const Labyrinth &labyrinth)
{
	std::ofstream outputFile(outputFileName);

	if (!outputFile.is_open())
	{
		std::cout << "Failed open \"" << outputFileName << "\" for writing." << "\n";
		PrintUserHelp(std::cout);
		return false;
	}

	PrintLabyrinth(outputFile, labyrinth);

	if (!outputFile.flush())
	{
		std::cout << "Failed to save data on disk.\n";
		return false;
	}

	return true;
}

bool WaveAlgorithm(const std::string &inputFileName, const std::string &outputFileName)
{
	Labyrinth labyrinth;

	if (!ReadLabyrinth(inputFileName, labyrinth))
	{
		return false;
	}
	
	WaveAlgorithm(labyrinth);

	if (!PrintLabyrinth(outputFileName, labyrinth))
	{
		return false;
	}

	return true;
}
