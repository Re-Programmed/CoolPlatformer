#include "PixelPerfectCollider.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
				//***TO DO***
				//Make collision data stored in a seprate location so you don't have to make a new array for every slope, there is just one static array for all of them.
			{
				PixelPerfectCollider::PixelPerfectCollider(PIXEL_COLLISION_FACE pixels[PixelColliderSize * PixelColliderSize])
				{
					for (uint16_t i = 0; i < PixelColliderSize * PixelColliderSize; i++)
					{
						m_pixels[i] = pixels[i];
					}
				}

				PixelPerfectCollider::~PixelPerfectCollider()
				{
					delete[PixelColliderSize] m_pixels;
				}

				void PixelPerfectCollider::Update(GLFWwindow* window, Objects::GameObject* object)
				{
					
				}

				PixelPerfectCollider::PIXEL_COLLISION_FACE PixelPerfectCollider::CheckPixel(MathUtils::Vec2 pixel)
				{
					return m_pixels[static_cast<int>((PixelColliderSize * pixel.Y) + pixel.X)];
				}
			}
		}
	}
}