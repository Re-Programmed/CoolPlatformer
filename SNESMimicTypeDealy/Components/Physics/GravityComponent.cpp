#include "GravityComponent.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			void GravityComponent::physicsTick(GLFWwindow* window, Objects::GameObject* object)
			{
				if (m_gravitationalVelocity < TerminalVelocity)
				{
					m_gravitationalVelocity -= GravityStrength;
				}

				object->Translate(Vec2(0, m_gravitationalVelocity));
			}

			void GravityComponent::Init(Objects::GameObject* object)
			{

			}

			void GravityComponent::SetGravitationalVelocity(float gVelocity)
			{
				m_gravitationalVelocity = gVelocity;
			}
		}
	}
}