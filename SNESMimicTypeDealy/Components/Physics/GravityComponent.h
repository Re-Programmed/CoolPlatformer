#pragma once
#include "../../Utils/Math/Vec2.h"
#include "./PhysicsComponent.h"
namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			using namespace MathUtils;
			class GravityComponent	//A GameObject that will be affected by gravity each frame.
				: public PhysicsComponent
			{
			public:
				GravityComponent() : PhysicsComponent(), m_gravitationalVelocity(0.f) {};
				void Init(Objects::GameObject* object);
				//Returns the current gravitational velocity.
				float GetGravitationalVelocity();	
				//Sets the current gravitational velocity.
				void SetGravitationalVelocity(float gVelocity);

				//Sets how much gravitational velocity should be applied each frame.
				void SetGravityStrength(float strength);
				//Gets how much gravitational velocity is being applied each frame (or I guess its technically speed as it has no direction. Although it does because it goes down so we are just passing and returning the magnitude but thats fine its still kind of velocity.)
				const float GetGravityStrength();

				//Set the maximum amount of force that can be applied to an object by gravity.
				void SetTerminalVelocity(float terminalVelocity);
			protected:
				float m_gravitationalVelocity;
				void physicsTick(GLFWwindow* window, Objects::GameObject* object) override;	//Called each physics update.

				void frameTick(GLFWwindow* window, Objects::GameObject* object) override; //Called each frame update.

				float m_gravityStrength = 0.2f;		//How much gravitational force should be applied each frame.
				float m_terminalVelocity = 60.f;	//The maximum amount of gravitational force to be applied.
			};
		}
	}
}