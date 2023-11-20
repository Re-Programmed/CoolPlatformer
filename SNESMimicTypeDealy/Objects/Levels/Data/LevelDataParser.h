#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "../../../Game/Level.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Levels
		{
			constexpr const int LevelDataSize = 7;

			//Parses the data from a level data file. ALWAYS DELETE DATA PARSER AFTER USE.
			class LevelDataParser
			{
			public:
				/// <summary>
				/// Calls each function in m_ops against each item in data respectivley.
				/// </summary>
				/// <param name="data">The level data.</param>
				LevelDataParser(std::string data[LevelDataSize], Game::Level& level);
				~LevelDataParser();
			private:
				static const std::function<void(std::string,Game::Level&)> m_ops[LevelDataSize];
			};
		}
	}
}