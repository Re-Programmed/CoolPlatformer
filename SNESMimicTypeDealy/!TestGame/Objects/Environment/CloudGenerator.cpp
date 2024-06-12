#include "CloudGenerator.h"
#include <random>
#include <iostream>
#include "../../../Rendering/Renderers/Renderer.h"
#include "../../Objects/Environment/BGParallax.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			uint8_t CloudGenerator::m_cloudCount = 0;
			uint8_t CloudGenerator::m_skyBeginY = 0;

			void CloudGenerator::GenerateClouds()
			{
				for (int i = 0; i < m_cloudCount; i++)
				{
					float x = (float)(std::rand() * (DEFAULT_LEVEL_SIZE_X << ChunkShift) / RAND_MAX);
					float y = (float)((std::rand() * ((DEFAULT_LEVEL_SIZE_Y << ChunkShift) - m_skyBeginY)) / RAND_MAX) + m_skyBeginY;

					std::cout << "------------------- CREATED CLOUD: " + Vec2(x, y).ToString() + "\n";

					//Sprites picked as either 1003, 1004, or 1005.
					BGParallax* cloud = new BGParallax({ x, y }, { 25, 25 }, Renderer::GetSprite((std::rand() * 3 / RAND_MAX) + 3), 0.75f);
					Renderer::InstantiateObject(Renderer::InstantiateGameObject(cloud, true, 2, true));
				}
			}
		}
	}
}