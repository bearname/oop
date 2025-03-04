// FlipByte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const unsigned VALID_ARGUMENT_COUNT = 2;
const unsigned MIN_INPUT_BYTE = 0;
const unsigned MAX_INPUT_BYTE = 255;
const short BYTE_SIZE = 8;

bool IsDecimalDigit(const std::string &str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

int StringToInt(const std::string &str, bool &wasError)
{
	int result = 0;
	try
	{
		result = stoi(str);
	}
	catch (const std::invalid_argument &e)
	{
		wasError = true;
		std::cerr << e.what() << "\n";
	}
	catch (const std::out_of_range &e)
	{
		wasError = true;
		std::cerr << e.what() << "\n";
	}
	return result;
}

uint8_t FlipByte(uint8_t byte)
{
	uint8_t result = 0;
	uint8_t temp = 0;
	for (short i = 0; i < BYTE_SIZE; i++)
	{
		temp = (byte & (1 << i));
		if (temp)
		{
			result |= (1 << ((8 - 1) - i));
		}
	}
	return result;
}

bool FlipByte(const std::string &byteStr)
{
	bool wasError = false;
	if (!IsDecimalDigit(byteStr))
	{
		std::cout << "The number must be positive decimal notation\n";
		return false;
	}
	int byteInt = StringToInt(byteStr, wasError);
	if (wasError)
	{
		return false;
	}
	if (byteInt < MIN_INPUT_BYTE || byteInt > MAX_INPUT_BYTE)
	{
		std::cout << "'" << byteInt << "' not included in the valid range [0, 255].\n";
		return false;
	}
	uint8_t byte = static_cast<uint8_t>(byteInt);
	byteInt = FlipByte(byte);
	std::cout << byteInt << "\n";
	return true;
}

int main(int argc, char* argv[])
{
	if (argc != VALID_ARGUMENT_COUNT)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: flipbyte.exe <input byte>\n";
		return 1;
	}
	std::string inputByteStr = argv[1];
	bool success = FlipByte(inputByteStr);
	if (!success)
	{
		return 1;
	}
    return 0;
}

