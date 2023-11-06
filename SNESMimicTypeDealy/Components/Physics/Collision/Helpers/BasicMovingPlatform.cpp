#include "BasicMovingPlatform.h"

namespace GAME_NAME::Components::Physics::Collision
{


	void BasicMovingPlatform::Update(GLFWwindow* window)
	{
		//Update the last position.
		m_lastPositionX = this->GetPosition().X;

		StaticBoxCollisionObject::Update(window);
	}
}
