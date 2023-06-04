#include "PhysicsComponent.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			void PhysicsComponent::Update(GLFWwindow* window, Objects::GameObject* object)
			{
				object->Translate(m_velocity);
				physicsTick(window, object);
			}
		}
	}
}