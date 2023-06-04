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

				StaticCollider* CollisionManager::m_staticColliders[STATIC_COLLIDER_LIMIT];
				ActiveCollider* CollisionManager::m_activeColliders[ACTIVE_COLLIDER_LIMIT];

				unsigned int CollisionManager::m_staticColliderCount(0);
				unsigned int CollisionManager::m_activeColliderCount(0);

				void CollisionManager::Update(GLFWwindow* window)
				{
					for (int i = 0; i < m_activeColliderCount; i++)
					{
						for (int x = 0; x < m_staticColliderCount; x++)
						{
							m_activeColliders[i]->CheckStaticCollisionShapes(m_staticColliders[x]);
						}
					}
				}

				void CollisionManager::InitStaticCollider(StaticCollider* staticCollider)
				{
					m_staticColliders[m_staticColliderCount] = staticCollider;
					m_staticColliderCount++;
				}

				void CollisionManager::InitActiveCollider(ActiveCollider* activeCollider)
				{
					m_activeColliders[m_activeColliderCount] = activeCollider;
					m_activeColliderCount++;
				}
			}
		}
	}
}