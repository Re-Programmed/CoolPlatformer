#pragma once
#include "ActiveCollider.h"

#define ROTATION_EDGE_DAMPING 0.75f

namespace GAME_NAME
{
	namespace Components::Physics::Collision
	{
		class RotationalBoxCollider final
			: public ActiveCollider
		{
		public:
			//Checks if this collider is currently colliding with another collider and calls Translate and m_onCollision appropriately.
			void CheckStaticCollisionShapes(StaticCollider* collider) override;
			//Checks if this collider is currently colliding with another ACTIVE collider and calls Translate and m_onCollision appropriately. Might also apply a backwards force.
			void CheckActiveCollisionShapes(ActiveCollider* collider) override;

			void Update(GLFWwindow* window, Objects::GameObject* object) override
			{

			}

			/// <summary>
			/// Returns true if the given point is to the left of right of the bottom edge of this collider based on the damping.
			/// </summary>
			/// <param name="xPoint"></param>
			/// <returns></returns>
			bool GetCollisionEdge(float xPoint);
		};
	}
}