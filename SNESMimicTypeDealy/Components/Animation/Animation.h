#pragma once
#include "../../Rendering/Sprite.h"
#include <vector>
#include "../../Objects/GameObject.h"

namespace GAME_NAME
{
	using namespace Rendering;

	namespace Components
	{
		namespace Animation
		{
#define ANIM_6_SPF 0.083f * 2.f /*12... FPS*/
#define ANIM_12_SPF 0.083f /*12... FPS*/
#define ANIM_16_SPF 0.0625f /*16 FPS*/


			struct AnimData						//Stores the data used for sprites in an animation.
			{
				std::vector<std::shared_ptr<Sprite>> Sprites;	//A list of pointers to the sprites that will be used in the animation.

				~AnimData()
				{
					
				}
			};

			class Animation
			{
			public:
				Animation(AnimData data, const float spf)	//AnimData should contain a list of sprites for the animation, spf is how many seconds pass between each frame.
					: m_data(data), m_speed(spf), m_currentFrame(0)
				{
					
				}

				/// <summary>
				/// Called when an animator switches the currently active animation to ensure the new animation to be played (this one) starts on the first frame.
				/// </summary>
				/// <param name="object"></param>
				void InitFrame(Objects::GameObject* object)
				{
					m_currentFrame = 0;

					if (object != nullptr)
					{
						object->SetSprite(m_data.Sprites[m_currentFrame]);
					}
				}

				void IncrementFrame(Objects::GameObject* object)	//Increase the current animation frame by one.
				{
					m_currentFrame++;

					if (m_currentFrame >= m_data.Sprites.size())
					{
						m_currentFrame = 0;
					}
					
					if (object != nullptr)
					{
						object->SetSprite(m_data.Sprites[m_currentFrame]);
					}
				}

				void DecrementFrame(Objects::GameObject* object)		//Decrease the current animation frame by one.
				{
					m_currentFrame--;

					if (m_currentFrame <= 0)
					{
						m_currentFrame = (int)m_data.Sprites.size() - 1;
					}

					object->SetSprite(m_data.Sprites[m_currentFrame]);
				}

				const float GetSpeed()								//Returns the SPF of the animation.
				{
					return m_speed;
				}

				inline int GetFrame()
				{
					return m_currentFrame;
				}

				inline unsigned int GetNumberOfFrames()
				{
					return m_data.Sprites.size();
				}

			private:
				const float m_speed;	//The SPF of the animation.
				const AnimData m_data;	//The sprites in the animation.

				int m_currentFrame;		//The current frame of animation.
			};


		}
	}
}