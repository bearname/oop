// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CMyArray.h"

int main()
{
	try
	{
		{
			CMyArray<int> arr;
			arr.Append(1);
			arr.Append(2);

			std::cout << "value : int\nclear and iteratate from Begin() to End()\nbefore clear\nsize: " << arr.GetSize() << "\n"
					  << "capacity: " << arr.GetCapacity() << "\n";

			for (auto it = arr.Begin(); it != arr.End(); ++it)
			{
				std::cout << *it << "\n";
			}

			arr.Clear();

			std::cout << "after clear\nsize: " << arr.GetSize() << "\n"
					  << "capacity: " << arr.GetCapacity() << "\n";

			for (auto it = arr.Begin(); it != arr.End(); ++it)
			{
				std::cout << *it << "\n";
			}
			std::cout << "\n";
		}
		{
			CMyArray<double> arr;

			for (int i = 0; i < 10; ++i)
			{
				arr.Append(i);
			}

			std::cout << "value : double\nResize:\nbefore clear\nsize: " << arr.GetSize() << "\n"
				<< "capacity: " << arr.GetCapacity() << "\n";

			for (auto it = arr.Begin(); it != arr.End(); ++it)
			{
				std::cout << *it << "\n";
			}
			std::cout << "\n";

			arr.Resize(2);

			std::cout << "after clear\nsize: " << arr.GetSize() << "\n"
					  << "capacity: " << arr.GetCapacity() << "\n";

			for (auto it = arr.Begin(); it != arr.End(); ++it)
			{
				std::cout << *it << "\n";
			}
			std::cout << "\n";
		}
		{
			CMyArray<std::string> arr;
			arr.Append("123");
			arr.Append("456");
			arr.Append("789");

			std::cout << "value : std::string\nreverse iterator:\n";

			for (auto it = arr.RBegin(); it != arr.REnd(); ++it)
			{
				std::cout << *it << "\n";
			}
			std::cout << "\n";
		}
	}
	catch (std::exception const& err)
	{
		std::cout << err.what() << "\n";
	}
	
	return 0;
}
