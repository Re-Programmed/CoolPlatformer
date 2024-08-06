#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME::Objects::Environment
{

	class BloodMark
		: public GameObject
	{
	public:
		BloodMark(GameObject* spawnObject, Vec2 midpoint);
	};
}