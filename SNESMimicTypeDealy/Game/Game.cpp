#include "Game.h"
#define GLFW_INCLUDE_NONE
#include "../Resources/AssetManager.h"
#include "../Objects/Levels/Data/LevelDataParser.h"
#include "../Rendering/Renderers/Renderer.h"

namespace GAME_NAME
{
	namespace Game
	{
		void Game::loadLevel(const char* levelPath, LEVEL_DATA dataToLoad, bool reload = false)
		{
			using namespace Resources;
			using namespace Objects;
			using namespace Levels;
			using namespace Rendering;

			if ((dataToLoad & LEVEL_DATA_AUDIO_MUSIC) != 0)
			{
				AssetManager::LoadMusic(levelPath, reload);
			}

			if ((dataToLoad & LEVEL_DATA_AUDIO_SFX) != 0)
			{
				/*LOAD SFX*/
			}

			if ((dataToLoad & LEVEL_DATA_TEXTURES_BACKGROUND) != 0)
			{
				AssetManager::LoadTextures(levelPath, BACKGROUND, reload);
			}

			if ((dataToLoad & LEVEL_DATA_TEXTURES_SPRITES) != 0)
			{
				AssetManager::LoadTextures(levelPath, SPRITES, reload);
			}

			if ((dataToLoad & LEVEL_DATA_DATA_CHUNKS) != 0)
			{
				std::vector<int> data;
				data = AssetManager::GetChunkData(levelPath);

				Renderer::InitChunks(data);
			}
			
			if ((dataToLoad & LEVEL_DATA_DATA_LEVEL) != 0)
			{
				std::string data[LevelDataSize];
				AssetManager::GetLevelData(levelPath, data);

				LevelDataParser* ldp = new LevelDataParser(data, m_level);

				delete data;
				delete ldp;
			}


		}

		Camera::Camera* Game::GetCamera()
		{
			return m_camera;
		}
	}
}
