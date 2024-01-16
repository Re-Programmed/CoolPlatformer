#include "LevelObjectHandler.h"
#include "../../!TestGame/TestGame.h"
#include "../../!TestGame/Mappings.h"
#include <fstream>

namespace GAME_NAME::Objects::Instantiate
{
	GameObject* LevelObjectHandler::GetLevelObject(std::string parent, std::string code)
	{
		using string = std::string;

		string objectFile = AssetPath;
		objectFile += TestGame::GetGlobalLevelData()->GetLevelPath();
		objectFile += ObjectSubfolder;
		objectFile += "/" + parent + ".pk";

		std::ifstream objectFileStream(objectFile);
		string line;

		uint32_t currentLine = 1;

		string currentObjectHeader;

		while (std::getline(objectFileStream, line, '\n'))
		{
			if (currentLine % 2 == 1)
			{
				currentObjectHeader = line;
			}
			else if(currentObjectHeader == code)
			{
				return GAME_NAME::Mappings::LoadObjectWithDefaultMapping(line);
			}

			currentLine++;
		}
	}
}

