#include "LevelManager.h"
#include "../TestGame.h"
#include "../Mappings.h"

namespace GAME_NAME::Level
{
	void LevelManager::LoadPlayerHouse()
	{
		//TestGame::INSTANCE->LoadLevel("/player_house_1_1", TestGame::LEVEL_DATA_TEXTURES_BACKGROUND);

		TestGame::INSTANCE->LoadLevel("/global_assets", TestGame::LEVEL_DATA_TEXTURES_SPRITES);

		TestGame::INSTANCE->LoadLevel("/player_house_1_1", (GAME_NAME::Game::Game::LEVEL_DATA)(TestGame::LEVEL_DATA_TEXTURES_BACKGROUND xor TestGame::LEVEL_DATA_ALL));

		GAME_NAME::Mappings::LoadObjectsWithDefaultMapping("/player_house_1_1");
		TestGame::INSTANCE->RenderFront = true;
	}
}

