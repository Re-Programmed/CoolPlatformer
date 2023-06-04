#pragma once
#include "../IComponent.h"
#include "../../Utils/Math/Vec2.h"
namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			using namespace MathUtils;
			class PhysicsComponent
				: public IComponent
			{
			public:
				PhysicsComponent() : m_velocity(Vec2::Zero) {}
				void Update(GLFWwindow* window, Objects::GameObject* object) final;
			protected:
				virtual void physicsTick(GLFWwindow* window, Objects::GameObject* object) = 0;
			protected:
				Vec2 m_velocity;
			};
		}
	}
}