#include "GravityComponent.h"
#include "../../Utils/Time/GameTime.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			int renderCalls = 0;
			float tAlloc = 0;
			float m_curr = 0;
			void GravityComponent::physicsTick(GLFWwindow* window, Objects::GameObject* object)
			{
				{
					renderCalls++;
					float t = glfwGetTime();
					tAlloc += t - m_curr;
					m_curr = t;

					if (tAlloc > 1.f)
					{
						tAlloc = 0.f;
						std::cout << "PHYS IN LAST SECOND: " << renderCalls << std::endl;
						renderCalls = 0;
					}
				}

				//std::cout << "TICK" << std::endl;
				if (m_gravitationalVelocity < m_terminalVelocity)
				{
					m_gravitationalVelocity -= m_gravityStrength;
				}

				object->Translate(Vec2(0, m_gravitationalVelocity * 0.017f));
			}

			void GravityComponent::Init(Objects::GameObject* object)
			{

			}

			float GravityComponent::GetGravitationalVelocity()
			{
				return m_gravitationalVelocity;
			}

			void GravityComponent::SetGravitationalVelocity(float gVelocity)
			{
				m_gravitationalVelocity = gVelocity;
			}
			void GravityComponent::SetGravityStrength(float strength)
			{
				m_gravityStrength = strength;
			}
			
			const float GravityComponent::GetGravityStrength()
			{
				return m_gravityStrength;
			}

			void GravityComponent::SetTerminalVelocity(float terminalVelocity)
			{
				m_terminalVelocity = terminalVelocity;
			}

		}
	}
}