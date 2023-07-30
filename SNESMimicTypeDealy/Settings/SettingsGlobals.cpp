#include "SettingsGlobals.h"
#include "AppDataFileManager.h"

namespace GAME_NAME
{
	namespace AppData
	{
		namespace Settings
		{
			UI16_AppDataGlobalVariable SettingsGlobals::MaxThreads("MaximumThreads");

			void SettingsGlobals::LoadAppDataVariables()
			{
				MaxThreads.Value = std::stoi(AppDataFileManager::GetValue("settings\\performance.dat", MaxThreads.VariableName, "32"));
			}
		}
	}
}