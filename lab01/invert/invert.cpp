// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "InvertMatrix.h"

const unsigned VALID_ARGUMENT_COUNT = 2;

bool Invert(const std::string &inputFileName);

int main(int argc, char* argv[])
{
	if (argc != VALID_ARGUMENT_COUNT)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: invert.exe <matrix file>\n";
		return 1;
	}

	std::string inputFileName = argv[1];
	bool success = Invert(inputFileName);
	if (!success)
	{
		return 1;
	}
	return 0;
}

bool Invert(const std::string &inputFileName)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		std::cout << "Failed open \"" << inputFileName << "\" for reading.\n";
		return false;
	}
	Matrix3x3 inputMatrix;
	InitMatrix(inputMatrix);
	bool success = ReadMatrix(inputFile, inputMatrix);
	if (!success)
	{
		std::cout << "Failed reading input matrix\n";
		return false;
	}
	Matrix3x3 invertMatrix;
	InitMatrix(invertMatrix);
	success = InvertMatrix(inputMatrix, invertMatrix);
	if (!success)
	{
		return false;
	}
	PrintMatrix(invertMatrix);
	return true;
}
