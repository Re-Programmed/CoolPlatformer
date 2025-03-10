#pragma once
#include "../../IComponent.h"
#include "../../../Objects/GameObject.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				//A collision object that will not be affected by collisions. (eg. The ground, it still collides but it does nothing when it collides.)
				class StaticCollider
					: public IComponent

				{
				public:
					StaticCollider()
						: ID(0), m_object(nullptr)
					{
						OnCollision = nullptr;
					};

					int ID;

					virtual void Update(GLFWwindow* window, Objects::GameObject* object) = 0;
					virtual void Init(Objects::GameObject* object) final
					{
						m_object = object;
					}

					Objects::GameObject* GetObject()
					{
						return m_object;
					}

					inline void SetBeforeCollision(void(*beforeCollision)(Objects::GameObject* self))
					{
						BeforeCollision = beforeCollision;
					}

					inline void SetOnCollision(bool(*onCollision)(GAME_NAME::MathUtils::Vec2 push, Objects::GameObject*, Objects::GameObject*))
					{
						OnCollision = onCollision;
					}

					//OnCollision is called when a collision occurs. It should return false if the collision occuring should be canceled. (push = how the object is being moved out of the collider.) (GameObject = this object)
					bool(*OnCollision)(GAME_NAME::MathUtils::Vec2 push, Objects::GameObject*, Objects::GameObject*);

					void(*BeforeCollision)(Objects::GameObject* self);
				protected:
					Objects::GameObject* m_object;


				};
			}
		}
	}
}