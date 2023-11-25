#pragma once

#ifndef _SPAWN_OBJECTS
#define _SPAWN_OBJECTS
#include "../../Objects/GameObject.h"
#include "../../Rendering/Renderers/Renderer.h"
#include "../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

#define LVLBUILDER_SPAWNABLE_COUNT 1


namespace GAME_NAME::Debug::LevelBuilder
{

	using namespace Objects;
	class SpawnObjects
	{
	public:
		typedef Renderer::InstantiateGameObject Spawnable;
	public:

		static Spawnable GetSpawnable(int index)
		{
using namespace GAME_NAME::Components::Physics::Collision;

			switch (index)
			{
			case 0:
				return Spawnable(new StaticBoxCollisionObject(Vec2::Zero, Vec2(32, 21), Rendering::Renderer::GetSprite(6)), false, 2, false); //Ground
			default:
				return Spawnable(new GameObject(Vec2::Zero, Vec2(32, 21), Rendering::Renderer::GetSprite(6)), false, 2, false); //Ground
			}
		}

	};
}

#endif