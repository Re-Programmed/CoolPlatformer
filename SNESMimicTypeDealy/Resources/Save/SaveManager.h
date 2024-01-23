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
		static void SaveBool(bool data, std::string vName)
		{
			SaveString(data ? "true" : "false", vName);
		}

		static void GetSaveString(std::string vName, std::string& value);
		static void GetSaveBool(std::string vName, bool& value)
		{
			std::string r(value ? "true" : "false");
			GetSaveString(vName, r);
			value = (r == "true");
		}

		static void SetCurrentFile(std::string fileName);
		
		inline static std::string GetCurrentFile()
		{
			return m_currentSaveFile;
		}
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