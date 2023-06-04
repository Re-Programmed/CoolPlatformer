#include "../ActiveBoxCollider.h"
#include "../CollisionManager.h"
#include "../../GravityComponent.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				using namespace MathUtils;



				class ActiveBoxCollisionGravityObject
					: public Objects::GameObject
				{
				public:

					ActiveBoxCollisionGravityObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite)
						: GameObject(position, scale, sprite), m_boxCollider(new ActiveBoxCollider()), m_gravity(new GravityComponent())
					{
						CollisionManager::InitActiveCollider(m_boxCollider);
						m_boxCollider->Init(this);
						m_gravity->Init(this);
						m_boxCollider->SetOnCollision(onCollision);
						m_boxCollider->SetBeforeUpdate(beforeUpdate);
					}

					~ActiveBoxCollisionGravityObject()
					{
						delete m_boxCollider;
						delete m_gravity;
					}

					bool GetActive()
					{
						return true;
					}
					
					void Update(GLFWwindow* window)
					{

					}

					void SetGravity(const float gVelocity)
					{
						m_gravity->SetGravitationalVelocity(gVelocity);
					}

				private:
					ActiveBoxCollider* const m_boxCollider;
					GravityComponent* const m_gravity;

					static void onCollision(Vec2 push, Objects::GameObject* obj)
					{
						if (push.Y > 0) { ((ActiveBoxCollisionGravityObject*)obj)->SetGravity(0.f); }
					}

					static void beforeUpdate(Objects::GameObject* obj)
					{
						((ActiveBoxCollisionGravityObject*)obj)->m_gravity->Update(nullptr, obj);
					}
				};

			}
		}
	}
}