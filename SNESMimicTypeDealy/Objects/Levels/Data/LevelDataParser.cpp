#include "LevelDataParser.h"

#if _DEBUG
#include "../../../Debug/DebugLog.h"
#endif

#include "../../../Audio/MusicManager.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Levels
		{
			const std::function<void(std::string,Game::Level&)> LevelDataParser::m_ops[LevelDataSize] {
					[](std::string title,Game::Level& level) { level.Name = title; },
					[](std::string id,Game::Level& level) { level.ID.World = id[0] + id[1]; level.ID.Level = id[2] + id[3]; },
					[](std::string song,Game::Level& level) { level.CurrentBGMusic = Audio::MusicManager::Play(std::stoi(song)); }
			};

			LevelDataParser::LevelDataParser(std::string data[LevelDataSize], Game::Level& level)
			{
#if _DEBUG
				DEBUG::DebugLog::Log("Parsing Level: " + data[0]);
#endif
				for (int i = 0; i < LevelDataSize; i++)
				{
					m_ops[i](data[i], level);
				}
			}

			LevelDataParser::~LevelDataParser()
			{
				
			}
		}
	}
}