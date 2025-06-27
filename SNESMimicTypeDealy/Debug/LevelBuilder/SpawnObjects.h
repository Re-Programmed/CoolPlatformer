#pragma once

#ifndef _SPAWN_OBJECTS
#define _SPAWN_OBJECTS
#include "../../Objects/GameObject.h"
#include "../../Rendering/Renderers/Renderer.h"
#include "../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

#define LVLBUILDER_SPAWNABLE_COUNT 3


namespace GAME_NAME::Debug::LevelBuilder
{

	using namespace Objects;
	class SpawnObjects
	{
	public:
		struct Spawnable {
			const std::vector<Renderer::InstantiateGameObject> Spawnables;

			Spawnable(std::vector<Renderer::InstantiateGameObject> objects)
				: Spawnables(objects)
			{
			
			}
		};
	public:

		//Delete spawnable after use.
		static Spawnable* GetSpawnable(int index)
		{
using namespace GAME_NAME::Components::Physics::Collision;

			std::vector<Renderer::InstantiateGameObject> v;

			switch (index)
			{
			case 0:
				v.emplace_back(new StaticBoxCollisionObject(Vec2::Zero, Vec2(32, 21), Rendering::Renderer::GetSprite(6)), false, 2, false);
				v.emplace_back(new GameObject(Vec2(0, 21), Vec2(32, 4), Rendering::Renderer::GetSprite(12)), false, 3, false);
				break;
			case 1:
				v.emplace_back(new GameObject(Vec2::Zero, Vec2(32, 30), Rendering::Renderer::GetSprite(23)), false, 2, false);
				break;
			case 2:
				v.emplace_back(new GameObject(Vec2::Zero, Vec2(32, 21), Rendering::Renderer::GetSprite(6)), false, 2, false);
				v.emplace_back(new GameObject(Vec2(0, 21), Vec2(32, 4), Rendering::Renderer::GetSprite(12)), false, 3, false);
				v.emplace_back(new StaticBoxCollisionObject(Vec2(0, 18.5), Vec2(32, 2.5), Rendering::Renderer::GetSprite(1)), false, 2, false); //MAKE NOT HIT FROM BOTTOM
				break;
			default:
				v.emplace_back(new StaticBoxCollisionObject(Vec2::Zero, Vec2(32, 21), Rendering::Renderer::GetSprite(6)), false, 2, false);
				break;
			}

			return new Spawnable(v); //Ground
		}

	};
}

#endif