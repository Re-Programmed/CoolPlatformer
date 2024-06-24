#pragma once
#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "../Utils/Math/Vec2.h"
#include "Camera/Camera.h"

namespace GAME_NAME
{
	constexpr static float TargetResolutionX = 320.f, TargetResolutionY = 180.f; //Resolution to scale sprites by.

	namespace Rendering
	{
		using namespace MathUtils;
		class Sprite	//Something drawn to the screen.
		{
		public:
			Sprite(const unsigned int spriteId) : m_spriteId(spriteId) {};								//spriteId should be the sprites buffer id. Sprites are loaded based on their position in the sprites directory.
			virtual void Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale, float rotation = 0.f);	//Render should be called to render a sprite to the screen.

#if _DEBUG
			//DEBUG
			inline std::string ToString()																//DEBUGGING
			{
				return "Sprite {" + std::to_string(this->m_spriteId) + "}";
			}
#endif

			static void SetResolution(Vec2 res);														//Sets the resolution scale of all sprites. This determines how to scale the sprites based on the resizing of the window. [Maintains scale no matter your resolution]

			const unsigned int GetSpriteId();															//Returns the sprite buffer index currently used.

		protected:
			static Vec2 m_resolutionScale;																//Resolution scale of all sprites.

			const unsigned int m_spriteId;																//Current sprite buffer ID.
		};
	}
}