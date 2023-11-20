#pragma once
#include "../../Objects/GameObject.h"
#include "../../Rendering/Renderers/Renderer.h"

#define LVLBUILDER_SPAWNABLE_COUNT 1

namespace GAME_NAME::Debug::LevelBuilder
{

	using namespace Objects;
	class SpawnObjects
	{
	public:
		typedef Renderer::InstantiateGameObject Spawnable;

	private:
		inline static Spawnable Spawnables[LVLBUILDER_SPAWNABLE_COUNT] = {
			 Spawnable(new GameObject(Vec2::Zero, Vec2(32,32), Rendering::Renderer::GetSprite(1), 0.0f), false, 2, false) //Ground
		};

	public:
		static Spawnable GetSpawnable(int index)
		{
			GameObject* obj = new GameObject(*Spawnables[index].MyObject);
			
			return Spawnable(obj, Spawnables[index].Active, Spawnables[index].Layer, Spawnables[index].Front);
		}

	};
}