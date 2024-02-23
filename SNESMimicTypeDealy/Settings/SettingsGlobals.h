#pragma once
#include <string>

namespace GAME_NAME
{
	namespace AppData
	{
		namespace Settings
		{
			typedef struct UI16_AppDataGlobalVariable
			{
				const std::string VariableName;
				uint16_t Value;

				UI16_AppDataGlobalVariable(std::string variableName)
					: VariableName(variableName), Value(0)
				{
				}
			};

			class SettingsGlobals
			{
			public:
				static UI16_AppDataGlobalVariable MaxThreads;

				static UI16_AppDataGlobalVariable WindowResolutionX;
				static UI16_AppDataGlobalVariable WindowResolutionY;

				static void LoadAppDataVariables();

				static void SaveUpdatedVariables();
			};
		}
	}
}