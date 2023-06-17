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
				//A collision object that will not be affected by collisions. (ie. The ground, it still collides but it does nothing when it collides.)
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