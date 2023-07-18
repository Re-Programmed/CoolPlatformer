#pragma once
#include "StaticCollider.h"
#include "../../../Utils/Math/iVec2.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				constexpr size_t PixelColliderSize = 16;	//How many pixels are in one pixel perfect collider.

				class PixelPerfectCollider final
					: public StaticCollider 
				{
				public:

					enum PIXEL_COLLISION_FACE : uint8_t	//WHAT SIDE OF THE OBJECT TO USE WHEN CHECKING COLLISION. USED WHEN DETERMINING WHICH WAY THE COLLIDER SHOULD BE PUSHED OUT.
					{
						PIXEL_COLLISION_FACE_LEFT,
						PIXEL_COLLISION_FACE_RIGHT,
						PIXEL_COLLISION_FACE_TOP,
						PIXEL_COLLISION_FACE_BOTTOM,

						PIXEL_COLLISION_FACE_NONE //No Collision
					};

				public:
					PixelPerfectCollider(PIXEL_COLLISION_FACE pixels[PixelColliderSize * PixelColliderSize]);		//Pixels should be [x][y].
					~PixelPerfectCollider();

					void Update(GLFWwindow* window, Objects::GameObject* object);			//Not used.
					PIXEL_COLLISION_FACE CheckPixel(MathUtils::Vec2 pixel);				//Get the value at a pixel.
				private:
					PIXEL_COLLISION_FACE m_pixels[PixelColliderSize * PixelColliderSize];	//The pixels to collide with. ([x], [y])
				};
			}
		}
	}
}