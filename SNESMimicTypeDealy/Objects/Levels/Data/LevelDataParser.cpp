#include "LevelDataParser.h"
#include "../../../Game/Game.h"

#if _DEBUG
#include "../../../Debug/DebugLog.h"
#endif


namespace GAME_NAME
{
	namespace Objects
	{
		namespace Levels
		{
			const std::function<void(std::string,Game::Level&)> LevelDataParser::m_ops[LevelDataSize] {
					[](std::string title,Game::Level& level) { level.Name = title; },
					[](std::string id,Game::Level& level) { level.ID.World = std::stoi(id); },
					[](std::string id,Game::Level& level) { level.ID.Level = std::stoi(id); },
					[](std::string song,Game::Level& level) { int snd = std::stoi(song); if (snd != -1) { Audio::AudioVoice voice = Audio::SoundManager::Play(snd, Audio::SoundManager::BGMusic); level.CurrentBGMusic = voice; Audio::SoundManager::BGMusic = voice; } },

					[](std::string playerX,Game::Level& level) { level.PlayerStartPosition.X = std::stoi(playerX); },
					[](std::string playerY,Game::Level& level) { level.PlayerStartPosition.Y = std::stoi(playerY); }
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