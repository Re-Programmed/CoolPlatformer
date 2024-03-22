#pragma once

#include <string>

#define SERIALIZED

namespace GAME_NAME
{
	class MiscState abstract
	{
	public:

		struct SaveParam
		{
			std::string Key;
			std::string Value;

			SaveParam(std::string key, std::string value) : Key(key), Value(value) {};
		};

		virtual void Decode(SaveParam params[]) = 0;
		virtual SaveParam* Encode(size_t& paramSize) = 0;
	};
}