#include "CollisionManager.h"
#include "StaticCollider.h"
#include "../../../Utils/CollisionDetection.h"

#include "../../../Debug/DebugLog.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				using namespace Utils;

				std::vector <StaticCollider*> CollisionManager::m_staticColliders;
				std::vector <ActiveCollider*> CollisionManager::m_activeColliders;

				void CollisionManager::UpdateAndClearBuffers()
				{
					for (ActiveCollider* activeCollider : m_activeColliders)
					{
						activeCollider->BeforeUpdate();
						//Collision for active colliders w/ eachother:
						for (ActiveCollider* activeCollider2 : m_activeColliders)
						{
							if (activeCollider != activeCollider2 && activeCollider->CollideWithOtherActive && activeCollider2->CollideWithOtherActive)
							{
								activeCollider->CheckActiveCollisionShapes(activeCollider2);
							}
						}

						for (StaticCollider* staticCollider : m_staticColliders)
						{
							activeCollider->CheckStaticCollisionShapes(staticCollider);
						}
					}

					m_staticColliders.clear();
					m_activeColliders.clear();
				}

				void CollisionManager::RegisterStaticColliderToBuffer(StaticCollider* staticCollider)
				{
					m_staticColliders.push_back(staticCollider);
				}

				void CollisionManager::RegisterActiveColliderToBuffer(ActiveCollider* activeCollider)
				{
					m_activeColliders.push_back(activeCollider);
				}

			}
		}
	}
}