#pragma once

#include <string>

#define APPDATA_SUBFOLDER "\\SNESMimicTypeDealy"

namespace GAME_NAME
{
	namespace AppData
	{
		/// <summary>
		/// Manages the AppData folder for your game.
		/// Can be used to store save data or settings.
		/// </summary>
		class AppDataFileManager
		{
		public:
			static void SetValue(std::string file, std::string variable, std::string value);				//Sets a value in a file. If no such file exists a file will be created. If the variable is not in the file it will be added.
			static std::string GetValue(std::string file, std::string variable, std::string defaultvalue);	//Gets a value from a file in the appdata directory. If no such file exists a file will be created. If the variable is not in the file it will be added.

			static void CreateAppDataFiles();		//Creates the AppData folder.

		private:
			static std::string m_appFolder;			//The AppData folder for your app. "C:/Users/<username>/AppData/Roaming/<appname>"
		};
	}
}