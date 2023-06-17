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
			struct AnimData						//Stores the data used for sprites in an animation.
			{
				std::vector<Sprite*> Sprites;	//A list of pointers to the sprites that will be used in the animation.

				~AnimData()
				{
					
				}
			};

			class Animation
			{
			public:
				Animation(AnimData data, const float fps)	//AnimData should contain a list of sprites for the animation, fps is how many times the frame should increment per second.
					: m_data(data), m_speed(fps)
				{
					
				}

				void IncrementFrame(Objects::GameObject* object)	//Increase the current animation frame by one.
				{
					m_currentFrame++;

					if (m_currentFrame >= m_data.Sprites.size())
					{
						m_currentFrame = 0;
					}
					object->SetSprite(m_data.Sprites[m_currentFrame]);
				}

				void DecrementFrame()								//Decrease the current animation frame by one.
				{
					m_currentFrame--;

					if (m_currentFrame <= 0)
					{
						m_currentFrame = m_data.Sprites.size() - 1;
					}
					m_data.Sprites[m_currentFrame];
				}

				const float GetSpeed()								//Returns the FPS of the animation.
				{
					return m_speed;
				}

			private:
				const float m_speed;	//The FPS of the animation.
				const AnimData m_data;	//The sprites in the animation.

				int m_currentFrame;		//The current frame of animation.
			};


		}
	}
}