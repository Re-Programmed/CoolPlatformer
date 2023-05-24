#pragma once
#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "../Utils/Math/Vec2.h"
#include "Camera/Camera.h"

namespace GAME_NAME
{

	namespace Rendering
	{
		using namespace MathUtils;
		class Sprite
		{
		public:
			Sprite(const unsigned int spriteId) : m_spriteId(spriteId) {};
			void Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale);

			//DEBUG
			std::string ToString();

		private:
			const unsigned int m_spriteId;
		};
	}
}