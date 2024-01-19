#include "base64.h"
#include <fstream>

namespace GAME_NAME::Resources
{
#define B64_PADDING_CHAR '='

	constexpr const char base64_characters[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string B64::Encode(std::string value)
	{
		std::string result = std::string();
		result.resize(((value.length() / 3) + value.length() % 3) * 4);

		int currResChar = 0, padding = 0;

		for (size_t i = 0; i < value.length(); i += 3)
		{
			int val = 0, loops = 0;

			for (int charid = i; charid <= i + 2 && charid < value.length(); charid++)
			{
				val = val << 8;
				val = val | value[charid];
				loops++;
			}

			int numBits = loops * 8;
			padding = numBits % 3;
			int temp, index;

			while (numBits != 0)
			{
				if (numBits >= 6)
				{
					temp = numBits - 6;

					index = (val >> temp) & 63;
					numBits -= 6;
				}
				else {
					temp = 6 - numBits;
					index = (val << temp) & 63;
					numBits = 0;
				}

				result[currResChar++] = base64_characters[index];
			}
		}

		for (int i = 1; i <= padding; i++)
		{
			result[currResChar++] = B64_PADDING_CHAR;
		}

		result[currResChar] = '\0';

		return result;
	}

	std::string B64::Decode(std::string value)
	{
		std::string result = std::string();
		result.resize(((value.length() / 4) + value.length() % 4) * 3);

		int currResChar = 0;

		for (size_t i = 0; i < value.length(); i += 4)
		{
			int val = 0, loops = 0;

			for (int charid = i; charid <= i + 3 && charid < value.size(); charid++)
			{
				val = val << 8;
				val = val | value[charid];
				loops++;
			}

			int numBits = loops * 8;
			int temp, index;

			while (numBits != 0)
			{
				result[currResChar++] = (val >> (numBits - 8)) & 255;
				numBits -= 8;
/*
				if (numBits >= 8)
				{
					temp = numBits - 8;
					index = (val >> temp) & 63;
					numBits -= 8;
				}
				else {
					temp = 8 - numBits;
					index = (val << temp) & 63;
					numBits = 0;
				}
				*/
			}

			result[currResChar] = '\0';

			return result;
		}
	}
}