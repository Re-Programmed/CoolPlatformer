#pragma once

#include <string>

namespace GAME_NAME
{
	template<class T>
	class MiscState
	{
	public:
		struct SaveParam
		{
			std::string Key;
			std::string Value;

			SaveParam(std::string key, std::string value) : Key(key), Value(value) {};
		};

		T Decode(SaveParam params[]) virtual;
		SaveParam* Encode(T) virtual;
	};
}