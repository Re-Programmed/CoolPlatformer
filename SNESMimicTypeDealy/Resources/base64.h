#pragma once
#include <string>

namespace GAME_NAME::Resources
{
	class B64
	{
	public:
		static std::string Encode(std::string value);
		static std::string Decode(std::string value);

	private:
	};
}