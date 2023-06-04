#include "AssetManager.h"
#include "../Rendering/Renderers/Renderer.h"
#include <string>
#include <fstream>
#include "../Audio/MusicManager.h"
#include "../Audio/SoundTypes/MusicTrack.h"

#if _DEBUG
#include "../Debug/DebugLog.h"

#define DebugHeader(x, y) { std::string s = x; DEBUG::DebugLog::LogPlain("------------------" + s + "------------------", y); }
#endif

namespace GAME_NAME
{

	namespace Resources
	{
		void AssetManager::LoadTextures(const char* subfolder, TEXTURE_LOAD textureLoad, bool reloadTextures)
		{
#if _DEBUG
			DebugHeader("Textures", textureLoad == BACKGROUND ? ";34" : ";36");
#endif
			std::string filePath = AssetPath;
			filePath += subfolder;
			
			if (reloadTextures) { Rendering::Renderer::ClearTextures(); }

			if (textureLoad == 0)
			{
				LoadTextures(subfolder, BACKGROUND);
				filePath += SpriteSubfolder;
			}
			else {
				filePath += (textureLoad == SPRITES ? SpriteSubfolder : BGSubfolder);
			}

			unsigned int i = 0;
			using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
			for (const auto& file : recursive_directory_iterator(filePath))
			{
				if (file.is_regular_file())
				{
#if _DEBUG
					DEBUG::DebugLog::Log(file.path().string(), false, ";34;2");
#endif
					if (textureLoad == SPRITES || textureLoad == ALL_TEXTURES)
					{
						Rendering::Renderer::LoadSprite(file.path().string().c_str());
					}
					else {
						Rendering::Renderer::LoadBG(file.path().string().c_str());
					}
				}
			}
#if _DEBUG
			DebugHeader("", ";34");
#endif
		}

		void AssetManager::LoadMusic(const char* subfolder, bool reloadMusic)
		{
#if _DEBUG
			DebugHeader("Music", ";2;33");
#endif
			std::string filePath = AssetPath;
			filePath += subfolder;
			filePath += MusicFilePath;

			if (reloadMusic) { Audio::MusicManager::ClearSources(); }

			unsigned int i = 0;
			using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

			for (const auto& file : recursive_directory_iterator(filePath))
			{
				if (file.is_regular_file())
				{
					Audio::MusicManager::RegisterAudioSource(new Audio::MusicTrack(file.path().string().c_str()));
#if _DEBUG
					DEBUG::DebugLog::Log(file.path().string(), false, ";33;2");
#endif
				}
			}

#if _DEBUG
			DebugHeader("", ";2;33");
#endif
		}

		void AssetManager::GetLevelData(const char* subfolder, std::string data[Objects::Levels::LevelDataSize])
		{
			std::string filePath = AssetPath;
			filePath += subfolder;
			filePath += LevelFileName;

			std::ifstream LevelFile(filePath);

			int8_t i = 0;
			std::string text;
			while (std::getline(LevelFile, text, '\n'))
			{
				data[i] = text;
				i++;
			}

		}

		std::vector<int> AssetManager::GetChunkData(const char* subfolder)
		{
			std::string filePath = AssetPath;
			filePath += subfolder;
			filePath += ChunkFileName;

			std::ifstream ChunkFile(filePath);
			std::string text;

			std::vector<int> data;

			while (std::getline(ChunkFile, text, ' '))
			{
				data.push_back(std::stoi(text));
			}

			return data;
		}

		void AssetManager::LoadObjectData(const char* subfolder, std::function<GameObject* (std::vector<std::string>)> mappings[], bool reloadObjects)
		{
			std::string filePath = AssetPath;
			filePath += subfolder;
			filePath += ObjectFileName;

			std::ifstream ObjectFile(filePath);
			std::string line;

			while (std::getline(ObjectFile, line, '\n'))
			{
				std::stringstream linestream(line);
				std::string component;
				
				std::function<GameObject* (std::vector<std::string>)>* mapping{};

				std::vector <std::string> v;

				int c = 0;
				while (std::getline(linestream, component, ','))
				{
					if (c == 0) { mapping = &mappings[std::stoi(component)]; }
					else { v.push_back(component); }
					c++; //C++ AHHAHAHAHAHAHH Like the language :)L::):)
				}

				GameObject* g = (*mapping)(v);

				if (g->GetActive())
				{
#if _DEBUG
					DEBUG::DebugLog::Log("[MAPPER] >>> Loading    L WAS ACTIVE", true, ";35");
#endif
					Renderer::LoadActiveObject(g);
				}
				else {
					Renderer::LoadObject(g);
				}

				//delete mapping;
			}
		}


		
	}
}