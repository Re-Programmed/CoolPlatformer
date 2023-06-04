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
				/// <summary>
				/// A collider that will not move or change.
				/// </summary>
				class StaticCollider
					: public IComponent

				{
				public:
					StaticCollider() {};

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