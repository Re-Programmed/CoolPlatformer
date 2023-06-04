#pragma once
#include "../../Objects/GameObject.h"
#include "../../Debug/DebugLog.h"
#include "../../Input/InputManager.h"
#include "../../Components/Physics/Collision/ActiveBoxCollider.h"
#include "../../Components/Physics/Collision/CollisionManager.h"

namespace GAME_NAME
{
	namespace Objects
	{
		using namespace Components;
		using namespace Physics;
		using namespace Collision;
		class DebugObject : public GameObject
		{
		public:
			void Update(GLFWwindow* window)
			{
				if (InputManager::GetKey(PLAYER_MOVE_UP))	
				{
					Translate(Vec2(0, 3));
				}

				m_boxCollider->Update(window, this);
			}

			DebugObject(Vec2 pos, Vec2 scale, Rendering::Sprite* sprite)
				: GameObject(pos, scale, sprite), m_boxCollider(new ActiveBoxCollider())
			{
				CollisionManager::InitActiveCollider(m_boxCollider);
				m_boxCollider->Init(this);
			}

		private:
			ActiveBoxCollider* const m_boxCollider;
		};
	}
}