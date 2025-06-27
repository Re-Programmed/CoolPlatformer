#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Rendering/Renderers/Renderer.h"

#include <memory>

namespace GAME_NAME::Objects::Environment
{

	class BloodMark
		: public GameObject
	{
	public:
		BloodMark(GameObject* spawnObject, Vec2 midpoint, Sprite* forceSprite = nullptr, Vec2 scale = Vec2::Zero);
	};
}