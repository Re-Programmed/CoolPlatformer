#pragma once
#include <string>

#define SAVE_SUBFOLDER_NAME "/saves"
#define SAVE_FILE_EXTENSION ".00.spk"
#define SM_AppData getAppdataFolder()

namespace GAME_NAME::Resources
{
	class SaveManager
	{
	public:
		static void SaveString(std::string data, std::string vName);

		static void SetCurrentFile(std::string fileName);
		
	private:
		static std::string m_currentSaveFile;

		static inline char* getAppdataFolder()
		{
			//Get APPDATA folder.
			char* appDataFolder;
			size_t len;
			errno_t err = _dupenv_s(&appDataFolder, &len, "APPDATA");
			return appDataFolder;
		}
	};
}