#pragma once
#include "../../IComponent.h"
#include "StaticCollider.h"
#include <functional>
#include "../../../Utils/Math/Vec2.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				template<typename Base, typename T>
				inline bool instanceof(const T* ptr) {
					return dynamic_cast<const Base*>(ptr) != nullptr;
				}

				/// <summary>
				/// A collider that will move or change.
				/// </summary>
				class ActiveCollider
					: public IComponent

				{
				public:
					ActiveCollider()
					{
						m_onCollision = nullptr;
					};

					virtual void Update(GLFWwindow* window, Objects::GameObject* object) = 0;
					virtual void Init(Objects::GameObject* object) final
					{
						m_object = object;
					}

					virtual void CheckStaticCollisionShapes(StaticCollider* collider) = 0;
					virtual void CheckActiveCollisionShapes(ActiveCollider* collider) = 0;

					void SetOnCollision(void(*onCollision)(GAME_NAME::MathUtils::Vec2 push, Objects::GameObject*))
					{
						m_onCollision = onCollision;
					}

					void SetBeforeUpdate(void(*beforeUpdate)(Objects::GameObject*))
					{
						m_beforeUpdate = beforeUpdate;
					}

					Objects::GameObject* GetObject()
					{
						return m_object;
					}

				protected:
					Objects::GameObject* m_object;
					void(*m_onCollision)(GAME_NAME::MathUtils::Vec2 push, Objects::GameObject*);
					void(*m_beforeUpdate)(Objects::GameObject*);
				};
			}
		}
	}
}