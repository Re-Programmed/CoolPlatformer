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
		typedef struct Spawnable
		{
			GameObject* Object;
			int textureId;
		};

	private:
		inline static Spawnable Spawnables[LVLBUILDER_SPAWNABLE_COUNT] = {
			 Spawnable(new GameObject(Vec2::Zero, Vec2::One * 32.f, Rendering::Renderer::GetSprite(1), 0.0f), 4) //Ground
		};

	public:
		static GameObject* GetSpawnable(int index)
		{
			GameObject* obj = new GameObject(*Spawnables[index].Object);
			obj->SetSprite(Renderer::GetSprite(Spawnables[index].textureId));
			return obj;
		}

	};
}