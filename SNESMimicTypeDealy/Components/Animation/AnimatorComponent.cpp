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

				if (m_tick >= m_animations[m_currentAnimation]->GetSpeed())
				{
					m_animations[m_currentAnimation]->IncrementFrame(object);
					m_tick = 0;
				}
			}

			void AnimatorComponent::Init(Objects::GameObject* object)
			{

			}

			inline void AnimatorComponent::SetCurrentAnimation(int8_t animation)
			{
				m_currentAnimation = animation;
			}

			
		}
	}
}