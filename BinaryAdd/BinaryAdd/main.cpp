#include <string>
#include <iostream>


typedef unsigned long long BinaryNum;

BinaryNum take_num()
{
	std::string num1_str;
	std::getline(std::cin, num1_str);

	BinaryNum num = 0;

	for (size_t i = 0; i < num1_str.length(); i++)
	{
		if (num1_str.at(i) == '1')
		{
			num += std::pow(2, num1_str.length() - i - 1);
		}
	}

	std::cout << "Got the number: " << std::to_string(num) << "\n";

	return num;
}

int main()
{
	BinaryNum n1 = take_num();
	BinaryNum n2 = take_num();

	BinaryNum res = 0;

	bool carryBit = 0;

	while (n1 > 0)
	{
		std::cout << "------------\n";
		std::cout << "N1: " << std::to_string(n1) << "\nN2: " << std::to_string(n2) << "\n";
		std::cout << "RES: " << std::to_string(res) << std::endl;

		if ((n1 | 1) xor (n2 | 1))
		{
			res <<= 1;
			if (!carryBit)
			{
				res |= 1;
			}
		}

		if ((n1 | 1) & (n2 | 1))
		{
			res <<= 1;
			if (carryBit)
			{
				res |= 1;
			}

			carryBit = 1;
		}

		n1 >>= 1;
	}
	
	std::cout << "\n\n\nResult of addition: " << res << std::endl;
}
