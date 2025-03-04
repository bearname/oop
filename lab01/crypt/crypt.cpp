// crypt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

enum class Action
{
	Crypt,
	Decrypt,
};

const int MIN_KEY = 0;
const int MAX_KEY = 255;
const std::string CRYPT_ACTION = "crypt";
const std::string DECRYPT_ACTION = "decrypt";

bool KeyInValidRange(int key)
{
	return MIN_KEY <= key && key <= MAX_KEY;
}

void PrintUserHelp()
{
	std::cout << "Usage for crypt: crypt.exe crypt <input file> <output file> <key>\n"
		<< "Usage for decrypt: crypt.exe decrypt <input file> <output file> <key>\n";
}

bool ParseAction(const std::string &actionStr, Action &action)
{
	if (actionStr == CRYPT_ACTION)
	{
		action = Action::Crypt;
		return true;
	}
	else if (actionStr == DECRYPT_ACTION)
	{
		action = Action::Decrypt;
		return true;
	}

	return false;
}

int StringToInt(const std::string &str, bool &wasError)
{
	int result = 0;
	try
	{
		result = stoi(str);
	}
	catch (const std::invalid_argument &err)
	{
		wasError = true;
		std::cerr << err.what() << "\n";
	}
	catch (std::out_of_range &err)
	{
		wasError = true;
		std::cerr << "Overflow: " << err.what() << "\n";
	}
	return result;
}

bool ParseKeyStr(const std::string &keyStr, int &key)
{
	bool wasError = false;
	key = StringToInt(keyStr, wasError);
	if (wasError || !KeyInValidRange(key))
	{
		std::cout << "The digit \"" << key << "\" not included in the valid range. ["
			<< MIN_KEY << "," << MAX_KEY << "]\n";
		return false;
	}
	return true;
}

char CryptMixingBitsOnByte(char ch)
{
	char result = (ch & 0b10000000) >> 2;
	result |= (ch & 0b01100000) >> 5;
	result |= (ch & 0b00011000) << 3;
	result |= (ch & 0b00000111) << 2;
	return result;
}

char CryptByte(char ch, int key)
{
	ch ^= key;
	return CryptMixingBitsOnByte(ch);
}

char DecryptMixingBitsOnByte(char ch)
{
	char result = (ch & 0b11000000) >> 3;
	result |= (ch & 0b00100000) << 2;
	result |= (ch & 0b00011100) >> 2;
	result |= (ch & 0b00000011) << 5;
	return result;
}

char DecryptByte(char ch, int key)
{
	ch = DecryptMixingBitsOnByte(ch);
	return ch ^= key;
}

void Crypt(std::istream &input, std::ostream &output, const Action &action, int key)
{
	std::function<char(char)> transformer;

	if (action == Action::Crypt)
	{
		transformer = [key](char ch)
		{
			return CryptByte(ch, key);
		};
	}
	else if (action == Action::Decrypt)
	{
		transformer = [key](char ch)
		{
			return DecryptByte(ch, key);
		};
	}

	std::transform(std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(output),
		transformer);
}

bool TransformFileContent(Action &action, const std::string &inputFileName,
	const std::string &outputFileName, int key)
{
	std::ifstream inputFile(inputFileName, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cout << "Failed open \"" << inputFileName << "\" for reading\n";
		PrintUserHelp();
		return false;
	}
	std::ofstream outputFile(outputFileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cout << "Failed read output file \"" << outputFileName << "\" for writing.\n";
		PrintUserHelp();
		return false;
	}

	Crypt(inputFile, outputFile, action, key);

	if (!outputFile.flush())
	{
		std::cout << "Failed to save data on disk.\n";
		return false;
	}

	return true;
}

const int VALID_ARGUMENT_COUNT = 5;

int main(int argc, char* argv[])
{
	if (argc != VALID_ARGUMENT_COUNT)
	{
		std::cout << "Invalid argument count\n";
		PrintUserHelp();
		return 1;
	}

	std::string actionStr = argv[1];
	Action action;
	if (!ParseAction(actionStr, action))
	{
		PrintUserHelp();
		return 1;
	}

	int key = 0;
	if (!ParseKeyStr(argv[4], key))
	{
		PrintUserHelp();
		return 1;
	}

	if (!TransformFileContent(action, argv[2], argv[3], key))
	{
		return 1;
	}

	return 0;
}
