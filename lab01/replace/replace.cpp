// replace.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;

static const int VALID_ARGUMENT_COUNT = 5;

string ReplaceAll(const string &str, const string &search, const string &replace);
void ReplaceStrOnFile(istream &input, ostream &output, const string &searchStr, const string &replaceStr);
bool ReplaceStrOnFile(const string &inputFileName, const string &outputFileName, const string &searchStr, const string &replaceStr);

int main(int argc, char* argv[])
{
	if (argc != VALID_ARGUMENT_COUNT)
	{
		cout << "Invalid argument count\n" 
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
	const string inputFileName = argv[1];
	const string outputFileName = argv[2];
	const string searchStr = argv[3];
	const string replaceStr = argv[4];
	bool success = ReplaceStrOnFile(inputFileName, outputFileName, searchStr, replaceStr);
	if (!success)
	{
		return 1;
	}
    return 0;
}

string ReplaceAll(const string &str, const string &search, const string &replace)
{
	size_t pos = 0;
	string result;
	for (size_t foundPos = 0; (foundPos = str.find(search, pos)) != string::npos; pos = foundPos + search.length())
	{
		result.append(str, pos, foundPos - pos);
		result.append(replace);
	}
	return result.append(str.substr(pos));
}

void ReplaceStrOnFile(istream &input, ostream &output, const string &searchStr, const string &replaceStr)
{
	string line;
	while (getline(input, line))
	{
		if (!searchStr.empty())
		{
			output << ReplaceAll(line, searchStr, replaceStr) << "\n";
		}
		else
		{
			output << line << "\n";
		}
	}
}

bool ReplaceStrOnFile(const string &inputFileName, const string &outputFileName, const string &searchStr, const string &replaceStr)
{
	ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed open \"" << inputFileName << "\" for reading.\n";
		return false;
	}
	ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		cout << "Failed open \"" << outputFileName << "\" for writing.\n";
		return false;
	}
	ReplaceStrOnFile(inputFile, outputFile, searchStr, replaceStr);
	if (!outputFile.flush())
	{
		cout << "Failed to save data on disk.\n";
		return false;
	}
	return true;
}