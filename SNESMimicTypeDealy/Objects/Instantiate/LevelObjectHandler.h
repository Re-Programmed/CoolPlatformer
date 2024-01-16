#pragma once
#include <string>
#include "../GameObject.h"

namespace GAME_NAME::Objects::Instantiate
{
	class LevelObjectHandler
	{
	public:
		static GameObject* GetLevelObject(std::string parent, std::string code);
	};
}