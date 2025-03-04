// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Dictonary.h"

namespace USER_COMMAND
{
const std::string Exit = "...";
const std::string Help = "@";
}

void PrintUserHelp(std::ostream& output)
{
	output << "exit - '...'\n"
		   << "help - '@'\n";
}

bool ReadDictionary(std::ostream& output, Dictionary& dictionary)
{
	std::ifstream dictionaryFile(dictionary.dictionaryFile);

	if (!dictionaryFile.is_open())
	{
		output << "Failed open \"" << dictionary.dictionaryFile << "\" for reading\n";
		return false;
	}

	if (!ReadDictionary(dictionaryFile, dictionary))
	{
		output << "The format of the dictionary file is as follows:\n"
			   << "<english word> : <russian word>\n";
		return false;
	}

	return true;
}

void Translate(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& wordToBeTranslate)
{
	std::string translation;

	if (Translate(dictionary, wordToBeTranslate, translation))
	{
		output << translation << "\n";
	}
	else
	{
		AddWordToDictionary(input, output, dictionary, wordToBeTranslate);
	}
}

void InteractWithUser(std::istream& input, std::ostream& output, Dictionary& dictionary)
{
	std::string userCommand;

	output << "> ";

	while (std::getline(input, userCommand))
	{
		if (userCommand == USER_COMMAND::Exit)
		{
			break;
		}
		else if (userCommand == USER_COMMAND::Help)
		{
			PrintUserHelp(output);
		}
		else
		{
			Translate(input, output, dictionary, userCommand);
		}

		output << "> ";
	}
}

bool SaveDictionary(std::ostream& output, const Dictionary& dictionary)
{
	std::ofstream outputFile(dictionary.dictionaryFile);

	if (!outputFile.is_open())
	{
		output << "Failed open \"" << dictionary.dictionaryFile << "\" for reading\n";
		return false;
	}

	PrintDictionary(outputFile, dictionary);

	if (!outputFile.flush())
	{
		output << "Failed to save data on disk.\n";
		return false;
	}

	output << "The changes are saved. So long.\n";

	return true;
}

bool AskConsentToSaveChanges(std::istream& input, std::ostream& output)
{
	output << "save the changes?(y/n): ";
	std::string userCommand;
	bool saveChange = false;

	output << "> ";

	while (std::getline(input, userCommand))
	{
		std::transform(userCommand.begin(), userCommand.end(), userCommand.begin(), ::tolower);

		if (userCommand == "y")
		{
			saveChange = true;
			break;
		}
		else if (userCommand == "n")
		{
			break;
		}
		else
		{
			output << "Invalid command. Try again. (y/n)\n";
		}

		output << "> ";
	}

	return saveChange;
}

bool SaveChangeToDictionary(std::istream& input, std::ostream& output, Dictionary& dictionary)
{
	if (dictionary.dictionaryFile.empty())
	{
		output << "Enter a file name to record the added words\n";
		std::getline(input, dictionary.dictionaryFile);
	}

	if (AskConsentToSaveChanges(input, output))
	{
		if (!SaveDictionary(output, dictionary))
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	Dictionary dictionary;

	if (argc == 2)
	{
		dictionary.dictionaryFile = argv[1];

		if (!ReadDictionary(std::cout, dictionary))
		{
			return 1;
		}
	}

	InteractWithUser(std::cin, std::cout, dictionary);

	if (dictionary.wasChange)
	{
		if (!SaveChangeToDictionary(std::cin, std::cout, dictionary))
		{
			return 1;
		}
	}

	return 0;
}