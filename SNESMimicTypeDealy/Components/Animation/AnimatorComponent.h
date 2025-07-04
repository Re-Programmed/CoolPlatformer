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

				/// <summary>
				/// Update the speed multiplier. (Lower values result in longer frames.)
				/// </summary>
				/// <param name="speedMult">How many times faster to make the animation.</param>
				inline void SetSpeedMult(double speedMult)
				{
					m_speedMult = speedMult;
				}

				inline void SetCurrentAnimation(int8_t animation, Objects::GameObject* forceFirstFrame = nullptr)						//Sets the current animation.
				{
					m_currentAnimation = animation;
					if(forceFirstFrame != nullptr){m_animations[m_currentAnimation]->InitFrame(forceFirstFrame);}
				}		

				inline int8_t GetCurrentAnimationIndex()
				{
					return m_currentAnimation;
				}

				inline std::shared_ptr<Animation> GetCurrentAnimation()
				{
					if (m_currentAnimation < 0) { return nullptr; }
					return m_animations[m_currentAnimation];
				}
				
				inline void SetAllowLooping(bool allowLooping)
				{
					m_allowLooping = allowLooping;
				}
			private:
				std::vector<std::shared_ptr<Animation>> m_animations;					//List of all possible animations this object can have.
				int8_t m_currentAnimation = -1;											//Current animation to use.

				double m_speedMult = 1.0;												//Speed multiplier for controling animation speed based on events. (Lower values result in longer frames.)

				double m_tick = 0.0;													//Storage for when to advance to the next frame.

				bool m_allowLooping = true;
			};



		}
	}
}