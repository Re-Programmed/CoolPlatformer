#pragma once
#include "../../Utils/Math/Vec2.h"
#include "./PhysicsComponent.h"
namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			constexpr const float GravityStrength = 1.f;
			constexpr const float TerminalVelocity = 60.f;

			using namespace MathUtils;
			class GravityComponent
				: public PhysicsComponent
			{
			public:
				GravityComponent() : PhysicsComponent(), m_gravitationalVelocity(0.f) {};
				void Init(Objects::GameObject* object);
				void SetGravitationalVelocity(float gVelocity);
			protected:
				float m_gravitationalVelocity;
				void physicsTick(GLFWwindow* window, Objects::GameObject* object);
			};
		}
	}
}