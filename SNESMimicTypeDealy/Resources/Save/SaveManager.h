#pragma once
#include <string>

#define SAVE_SUBFOLDER_NAME "/saves"
#define SAVE_FILE_EXTENSION ".00.spk"
#define SM_AppData getAppdataFolder()

#define SAVE_MNG_TRUE_STATE 't'
#define SAVE_MNG_FALSE_STATE 'f'
#define SAVE_MNG_STATE(x) (x ? SAVE_MNG_TRUE_STATE : SAVE_MNG_FALSE_STATE)

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

		static void SaveLevelString(std::string data, size_t levelID);
		static void GetLevelString(std::string& data, size_t levelID);

		static void GetSaveString(std::string vName, std::string& value);
		static void GetSaveBool(std::string vName, bool& value)
		{
			std::string r(value ? "true" : "false");
			GetSaveString(vName, r);
			value = (r.starts_with("true"));
		}

		static void SetCurrentFile(std::string fileName);
		inline static void SetCurrentLevelFile(std::string fileName)
		{
			m_currentLevelSaveFile = fileName;
		}

		inline static std::string GetCurrentFile()
		{
			return m_currentSaveFile;
		}

		inline static std::string GetCurrentLevelFile()
		{
			return m_currentLevelSaveFile;
		}
	private:
		static std::string m_currentSaveFile;
		static std::string m_currentLevelSaveFile;

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