#pragma once
#include "../../IComponent.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				//A collision object that will not be affected by collisions. (eg. The ground, it still collides but it does nothing when it collides.)
				class StaticCollider
					: public IComponent

				{
				public:
					int ID;

					virtual void Update(GLFWwindow* window, Objects::GameObject* object) = 0;
					virtual void Init(Objects::GameObject* object) final
					{
						m_object = object;
					}

					Objects::GameObject* GetObject()
					{
						return m_object;
					}

				protected:
					Objects::GameObject* m_object;
				};
			}
		}
	}
}