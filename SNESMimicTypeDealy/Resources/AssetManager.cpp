#include "AssetManager.h"
#include "../Rendering/Renderers/Renderer.h"
#include <string>
#include <fstream>
#include "../Audio/SoundManager.h"
#include "../Audio/SoundTypes/Sound.h"
#include "../Settings/SettingsGlobals.h"
#include <regex>

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
					GLuint myLoaded = 0;
#endif
					if (textureLoad == SPRITES || textureLoad == ALL_TEXTURES)
					{
						i++;
#if _DEBUG
						myLoaded = Rendering::Renderer::LoadSprite(file.path().string().c_str());
#else
						Rendering::Renderer::LoadSprite(file.path().string().c_str());
#endif
					}
					else {
#if _DEBUG
						myLoaded = Rendering::Renderer::LoadBG(file.path().string().c_str());
#else
						Rendering::Renderer::LoadBG(file.path().string().c_str());
#endif
					}

#if _DEBUG
					DEBUG::DebugLog::Log(std::to_string(myLoaded) + ":: " + file.path().string(), false, ";34;2");
#endif
				}
			}

			if (textureLoad == SPRITES || textureLoad == ALL_TEXTURES)
			{
				//Assign the first set of loaded sprites to be the fileOffset. (Negative sprite indicies)
				if (Renderer::GetLastFileOffest() == -1)
				{
					Renderer::SetLastFileOffset(0);
				}
				else if(Renderer::GetLastFileOffest() == 0)
				{
					Renderer::SetLastFileOffset(Renderer::GetSpriteCount() - i);
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

			if (reloadMusic) { Audio::SoundManager::ClearSources(); }

			using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

			for (const auto& file : recursive_directory_iterator(filePath))
			{
				if (file.is_regular_file())
				{
					Audio::SoundManager::RegisterAudioSource(std::make_shared<GAME_NAME::Audio::Sound>(file.path().string().c_str()));
#if _DEBUG
					DEBUG::DebugLog::Log(file.path().string(), false, ";33;2");
#endif
				}
			}

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

		void loadObjectDataThread(std::string line, std::function<void(std::vector<std::string>)> mappings[])
		{
			std::stringstream linestream(line);
			std::string component;

			std::function<void(std::vector<std::string>)>* mapping{};

			std::vector <std::string> v;

			int c = 0;
			while (std::getline(linestream, component, ','))
			{
				
				if (c == 0) { mapping = &mappings[std::stoi(component)]; }
				else {
					//Allows for the use of "5|4+" to mean 5+4=9 and plug 9 in for that variable in object.pk.
					int decodedComponent = 0;

					if (component.ends_with("+"))
					{
						component.erase(component.length() - 1);

						std::string decodedAddition = "";
						while (!component.ends_with("|"))
						{
							decodedAddition = component.at(component.length() - 1) + decodedAddition;
							component.erase(component.length() - 1);
						}

						component.erase(component.length() - 1);

						decodedComponent = std::stoi(decodedAddition) + std::stoi(component);
					}

					v.push_back(decodedComponent != 0 ? std::to_string(decodedComponent) : component);
				
				}
				c++; //C++ AHHAHAHAHAHAHH Like the language :)L::):)
			}

			(*mapping)(v);

			//delete mapping;	

		}

		void AssetManager::LoadObjectData(const char* subfolder, std::function<void (std::vector<std::string>)> mappings[], bool reloadObjects)
		{
			std::string filePath = AssetPath;
			filePath += subfolder;
			filePath += ObjectFileName;

			std::ifstream ObjectFile(filePath);
			std::string line;

			std::vector<std::string> definedMacros;	//Stores a list of strings representing the templates that macros will use.

			std::vector<std::thread*> threads;
			int thCurr = 0;

			bool declaringMacro = false;

			while (std::getline(ObjectFile, line, '\n'))
			{
				if (line.empty() || line.starts_with(";")) { continue; } //For line breaks or lines beginning with a ";" do nothing. (useful for comments etc.)

#pragma region MacroDetection
				//Check if the line is declaring a macro.
				if (line.starts_with("-->"))
				{
					declaringMacro = !declaringMacro;
					
					if (declaringMacro)
					{
						definedMacros.push_back(std::regex_replace(line, std::regex("-->"), ""));
					}

					continue;
				}

				//Will continue defining a macro until another "-->" is found allowing for multi line macros.
				if (declaringMacro)
				{
					definedMacros[definedMacros.size() - 1] = definedMacros[definedMacros.size() - 1] + std::regex_replace(line, std::regex(" "), "");
					continue;
				}

				//Check if the line is using a macro.
				if (line.starts_with("<--"))
				{
					std::string resultingData;

					std::string s = std::regex_replace(line, std::regex("<--"), "");

					std::stringstream macrostream(s);
					std::string component;

					int c = 0;
					while (std::getline(macrostream, component, ','))
					{
						//First entry to the macro is which macro to use.
						if (c == 0)
						{
							int macro = std::stoi(component);
							resultingData = definedMacros[macro];
							c = 1;
							continue;
						}

						//Subsequent entries will be placed into the macro at %(c).
						resultingData = std::regex_replace(resultingData, std::regex("%" + std::to_string(c)), component == "null" ? "" : component);
						c++;
					}

					std::stringstream multiobjectmacrostream(resultingData);

					//If we have multiple objects in the macro to be defined they are separated by ;.
					while (std::getline(multiobjectmacrostream, component, ';'))
					{
						//Start the loading thread for the macro.
						threads.push_back(new std::thread(loadObjectDataThread, component, mappings));
						thCurr++;
					}

					goto checkthreads;
				}
#pragma endregion


				threads.push_back(new std::thread(loadObjectDataThread, line, mappings));
				thCurr++;

	checkthreads:
				if (thCurr == AppData::Settings::SettingsGlobals::MaxThreads.Value)
				{
					for (int i = 0; i < thCurr; i++)
					{
						if (threads[i] != nullptr && threads[i]->joinable())
						{
							threads[i]->join();
							//delete threads[i];
						}
					}

					thCurr = 0;
				}
			}

			for (int i = 0; i < thCurr; i++)
			{
				if (threads[i] != nullptr && threads[i]->joinable())
				{
					threads[i]->join();
					//delete threads[i];
				}
			}

			//delete[definedMacrosCount] definedMacros;
		}


		
	}
}