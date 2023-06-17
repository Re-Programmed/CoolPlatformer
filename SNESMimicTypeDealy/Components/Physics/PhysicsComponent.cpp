#include "PhysicsComponent.h"
#include "../../Utils/Time/GameTime.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			void PhysicsComponent::Update(GLFWwindow* window, Objects::GameObject* object)
			{
				object->Translate(m_velocity * Utils::Time::GameTime::GetScaledDeltaTime());

				xAirDrag();
				yAirDrag();

				physicsTick(window, object);
			}

			void PhysicsComponent::xAirDrag()
			{
				if (m_frictionDrag == 0) { return; }

				if (m_velocity.X <= -m_frictionDrag)
				{
					m_velocity += Vec2(m_frictionDrag, 0);
				}
				else if (m_velocity.X >= m_frictionDrag)
				{
					m_velocity -= Vec2(m_frictionDrag, 0);
				}
				else {
					m_velocity = Vec2(0, m_velocity.Y);
				}
			}

			void PhysicsComponent::yAirDrag()
			{
				if (m_airDrag == 0) { return; }

				if (m_velocity.Y <= -m_airDrag)
				{
					m_velocity += Vec2(0, m_airDrag);
				}
				else if (m_velocity.Y >= m_airDrag)
				{
					m_velocity -= Vec2(0, m_airDrag);
				}
				else {
					m_velocity = Vec2(m_velocity.X, 0);
				}
			}

			void PhysicsComponent::SetVelocity(Vec2 velocity)
			{
				m_velocity = velocity;
			}

			void PhysicsComponent::SetVelocityX(float X)
			{
				m_velocity.X = X;
			}

			void PhysicsComponent::SetVelocityY(float Y)
			{
				m_velocity.Y = Y;
			}

			Vec2 PhysicsComponent::GetVelocity()
			{
				return m_velocity;
			}

			void PhysicsComponent::AddVelocity(Vec2 velocity)
			{
				m_velocity += velocity;
			}

			void PhysicsComponent::SetFrictionDrag(float friction)
			{
				m_frictionDrag = friction;
			}
		}
	}
}