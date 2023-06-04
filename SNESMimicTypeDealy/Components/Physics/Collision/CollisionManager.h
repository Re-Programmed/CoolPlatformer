#pragma once
#include "../../../Utils/IUpdateable.h"
#include "ActiveCollider.h"
#include "StaticCollider.h"

#define STATIC_COLLIDER_LIMIT 100
#define ACTIVE_COLLIDER_LIMIT 15

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				class CollisionManager final
					: public Utils::IUpdateable
				{
				public:
					void Update(GLFWwindow* window);

					static void InitStaticCollider(StaticCollider* staticCollider);
					static void InitActiveCollider(ActiveCollider* activeCollider);
				private:
					static StaticCollider* m_staticColliders[STATIC_COLLIDER_LIMIT];
					static ActiveCollider* m_activeColliders[ACTIVE_COLLIDER_LIMIT];

					static unsigned int m_staticColliderCount;
					static unsigned int m_activeColliderCount;
				};
			}
		}
	}
}