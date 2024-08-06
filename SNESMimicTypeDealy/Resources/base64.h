#pragma once
#include <string>
#include <vector>

namespace GAME_NAME::Resources
{
	class B64
	{
	public:
		static std::string Encode(std::string value);
		static std::string Decode(std::string value);

		static std::vector<unsigned char> DecodeToBytes(std::string const& value);
	private:
	};
}