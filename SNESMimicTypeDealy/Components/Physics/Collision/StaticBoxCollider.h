#pragma once
#include "./StaticCollider.h"

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
				class StaticBoxCollider final
					: public StaticCollider
					
				{
				public:
					StaticBoxCollider() {};

					void Update(GLFWwindow* window, Objects::GameObject* object);
				};
			}
		}
	}
}