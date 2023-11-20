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
			/// <summary>
			/// name
			/// world
			/// level
			/// song
			/// playerX
			/// playerY
			/// </summary>
			const std::function<void(std::string,Game::Level&)> LevelDataParser::m_ops[LevelDataSize] {
					[](std::string title,Game::Level& level) { level.Name = title; },
					[](std::string id,Game::Level& level) { level.ID.World = std::stoi(id); },
					[](std::string id,Game::Level& level) { level.ID.Level = std::stoi(id); },

					[](std::string song,Game::Level& level)
					{
						int snd = std::stoi(song);
						if (snd != -1) 
						{ 
							Audio::AudioVoice voice = Audio::SoundManager::Play(snd, Audio::SoundManager::BGMusic);
							level.CurrentBGMusic = voice;
							Audio::SoundManager::BGMusic = voice;
						}
					},

					[](std::string playerX,Game::Level& level) { level.PlayerStartPosition.X = std::stoi(playerX); },
					[](std::string playerY,Game::Level& level) { level.PlayerStartPosition.Y = std::stoi(playerY); },
					[](std::string levelColor, Game::Level& level) {
						std::stringstream read(levelColor);
						std::string component;
						Vec3 color;
						uint8_t i = 0;

						while (std::getline(read, component, ','))
						{
							switch (i)
							{
							case 0:
								color.X = static_cast<float>(std::stoi(component)) / 255.f;
								break;
							case 1:
								color.Y = static_cast<float>(std::stoi(component)) / 255.f;
								break;
							case 2:
								color.Z = static_cast<float>(std::stoi(component)) / 255.f;
								break;
#if _DEBUG
							default:
								DEBUG::DebugLog::LogWarning("[LEVEL DATA PARSER] expected 3 components for a level color, got " + std::to_string(i + 1) + ".");
								break;
#endif
							}

							i++;
						}

						level.BackgroundColor = color;
					}
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