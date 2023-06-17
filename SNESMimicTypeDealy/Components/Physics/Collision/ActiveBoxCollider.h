#pragma once
#include "./ActiveCollider.h"
#include "StaticBoxCollider.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				//A collider affected by collisions.
				class ActiveBoxCollider final
					: public ActiveCollider

				{
				public:
					ActiveBoxCollider() {};

					void Update(GLFWwindow* window, Objects::GameObject* object);

					void CheckStaticCollisionShapes(StaticCollider* collider);	//Checks if this collider is currently colliding with another collider and calls Translate and m_onCollision appropriately.
					void CheckActiveCollisionShapes(ActiveCollider* collider);	//Checks if this collider is currently colliding with another ACTIVE collider and calls Translate and m_onCollision appropriately. Might also apply a backwards force.
				};
			}
		}
	}
}