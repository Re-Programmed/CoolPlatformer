#include "base64.h"
#include <fstream>

namespace GAME_NAME::Resources
{
#define B64_PADDING_CHAR '='
#define B64_CHARACTER_COUNT 65

	constexpr const char base64_characters[B64_CHARACTER_COUNT] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//constexpr const char base64_characters[B64_CHARACTER_COUNT] = "!@#$%^&*()-=_+789456123/\\|;:'\"[]{}<>,.?qazwsxedcrfvtgbyhnujmikol";

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
		const size_t expectedSize = ((value.length() / 4) + value.length() % 4) * 3;
		result.resize(expectedSize);

		unsigned int currResChar = 0;

		int val = 0;
		size_t i;
		for (i = 0; i < value.length(); i++)
		{
			const char currentChar = value[i];

			if (currentChar != B64_PADDING_CHAR)
			{
				for (uint16_t bIndex = 0; bIndex < B64_CHARACTER_COUNT; bIndex++)
				{
					if (currentChar == base64_characters[bIndex])
					{
						val = val << 6;
						val |= bIndex & 63;
						break;
					}
				}
			}

			if (val >> 18 != 0)
			{
				int currentBits = 16;
				while (currentBits >= 0)
				{
					char rChar = (static_cast<char>((val >> currentBits) & 255));
					result[currResChar++] = rChar;
					currentBits -= 8;
				}

				val = 0;
			}

		}

		result[currResChar] = '\0';
		return result;
	}
}