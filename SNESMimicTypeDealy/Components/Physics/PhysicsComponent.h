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
			class PhysicsComponent	//A component that can manage the velocity of an object.
				: public IComponent
			{
			public:
				PhysicsComponent() : m_velocity(Vec2::Zero), m_frictionDrag(1.f), m_airDrag(0.02f) {}
				void Update(GLFWwindow* window, Objects::GameObject* object) final;

				void SetVelocity(Vec2 velocity);

				void SetVelocityX(float X);
				void SetVelocityY(float Y);

				Vec2 GetVelocity();

				void AddVelocity(Vec2 velocity);
				
				/// <summary>
				/// Sets how much the object will slow down when moving left and right on the ground.
				/// </summary>
				/// <param name="airResistance"></param>
				void SetFrictionDrag(float airResistance);

			protected:
				virtual void physicsTick(GLFWwindow* window, Objects::GameObject* object) = 0; //Called each physics update.
			protected:
				Vec2 m_velocity;
				float m_frictionDrag;	//How much X velocity is subtracted each frame.
				float m_airDrag;		//How much Y velocity is subtracted each frame.

			private:
				void xAirDrag();		//Calculate X drag and clamp velocity.
				void yAirDrag();		//Calculate Y drag and clamp velocity.
			};
		}
	}
}