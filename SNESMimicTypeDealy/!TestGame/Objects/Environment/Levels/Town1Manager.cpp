#include "Town1Manager.h"
#include "../../../../Rendering/Renderers/Renderer.h"

#include "../BGParallax.h"

namespace GAME_NAME::Objects::Environment::Levels
{
	void Town1Manager::InitLevel()
	{
		spawnWindmills();
	}

#define WINDMILL_SPACING 600
#define WINDMILL_RAND() (std::rand() * WINDMILL_SPACING / RAND_MAX)
	void Town1Manager::spawnWindmills()
	{
		int i = 0;
		while (i < DEFAULT_LEVEL_SIZE_X << ChunkShift)
		{
			i += WINDMILL_RAND();

			BGParallax* windmill = new BGParallax({ (float)i, 0.f }, { 96.f, 128.f }, Renderer::GetSprite(73), 2.f);
			Renderer::LoadActiveObject(windmill, 0);
		}
	}
}
