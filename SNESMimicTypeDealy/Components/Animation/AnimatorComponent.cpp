#include "AnimatorComponent.h"
#include "../../Utils/Time/GameTime.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Animation
		{
			AnimatorComponent::AnimatorComponent(std::vector<std::shared_ptr<Animation>> animations)
				: m_animations(animations)
			{
				
			}

			AnimatorComponent::~AnimatorComponent()
			{

			}

			void AnimatorComponent::Update(GLFWwindow* window, Objects::GameObject* object)
			{
				if (m_currentAnimation == -1) { return; }
				m_tick += GAME_NAME::Utils::Time::GameTime::GetScaledDeltaTime();

				if (m_tick * std::abs(m_speedMult) >= m_animations[m_currentAnimation]->GetSpeed())
				{
					if (!m_allowLooping)
					{
						//Trying to loop.
						if (m_speedMult < 0.0 ? (m_animations[m_currentAnimation]->GetFrame() == 0) : (m_animations[m_currentAnimation]->GetFrame() + 1 >= m_animations[m_currentAnimation]->GetNumberOfFrames()))
						{
							//Cancels the current animation now that it has finished.
							m_tick = 0.0;
							m_currentAnimation = -1;
							return;
						}
					}

					if (m_speedMult < 0.0)
					{
						m_animations[m_currentAnimation]->DecrementFrame(object);
					}
					else {
						m_animations[m_currentAnimation]->IncrementFrame(object);
					}
					m_tick = 0.0;
				}
			}

			void AnimatorComponent::Init(Objects::GameObject* object)
			{

			}

			

			
		}
	}
}