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
				/// <summary>
				/// A collider that will not move or change.
				/// </summary>
				class ActiveBoxCollider final
					: public ActiveCollider

				{
				public:
					ActiveBoxCollider() {};

					void Update(GLFWwindow* window, Objects::GameObject* object);

					void CheckStaticCollisionShapes(StaticCollider* collider);
					void CheckActiveCollisionShapes(ActiveCollider* collider);
				};
			}
		}
	}
}