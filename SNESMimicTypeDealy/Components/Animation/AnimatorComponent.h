#pragma once

#include "../IComponent.h"
#include "./Animation.h"
#include <algorithm>
#include <memory>

namespace GAME_NAME
{
	namespace Components
	{
		namespace Animation
		{


			class AnimatorComponent		//Added to objects to provide animations that can be switched between.
				: public IComponent
			{
			public:
				AnimatorComponent(std::vector<std::shared_ptr<Animation>> animations);	//Provide a list of all the available animations the object can use in order. (ex. walking, running, jumping)
				~AnimatorComponent();

				void Update(GLFWwindow* window, Objects::GameObject* object);			//Called each frame to increment the timer that waits for the next frame.
				void Init(Objects::GameObject* object);

				inline void SetCurrentAnimation(int8_t animation);						//Sets what animation the object is currently using. The animation param is the index of the animation to use in the array that was initially provided.
			private:
				std::vector<std::shared_ptr<Animation>> m_animations;					//List of all possible animations this object can have.
				int8_t m_currentAnimation = 0;											//Current animation to use.

				float m_tick = 0.f;														//Storage for when to advance to the next frame.
			};



		}
	}
}