#pragma once
#include "../../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GAME_NAME::Level
{
	class LevelSystem
	{
	public:
		virtual void Update(GLFWwindow* window) = 0;
	};
}