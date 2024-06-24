#include "GravityComponent.h"
#include "../../Utils/Time/GameTime.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			/* ---RENDER UPDATE COUNTER---
			int renderCalls = 0; //TODO: REMOVE
			double tAlloc = 0;
			double m_curr = 0;
			*/
			void GravityComponent::physicsTick(GLFWwindow* window, Objects::GameObject* object)
			{
				/* ---RENDER UPDATE COUNTER---
				{
					renderCalls++;
					double t = glfwGetTime();
					tAlloc += t - m_curr;
					m_curr = t;

					if (tAlloc > 1.f)
					{
						tAlloc = 0.f;
						std::cout << "PHYS IN LAST SECOND: " << renderCalls << std::endl;
						renderCalls = 0;
					}
				} */

				//std::cout << "TICK" << std::endl;
				if (m_gravitationalVelocity < m_terminalVelocity)
				{
					m_gravitationalVelocity -= m_gravityStrength;
				}
			}

			void GravityComponent::frameTick(GLFWwindow* window, Objects::GameObject* object)
			{
				object->Translate(Vec2(0, m_gravitationalVelocity * GAME_NAME::Utils::Time::GameTime::GetScaledDeltaTime()));
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