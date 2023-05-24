#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include "../Rendering/Window.h"

///How many inputs to check for
#define KEY_ARRAY_SIZE 4

namespace GAME_NAME
{

	enum keyRef
	{
		PLAYER_MOVE_UP = 0,
		PLAYER_MOVE_DOWN = 1,
		PLAYER_MOVE_LEFT = 2,
		PLAYER_MOVE_RIGHT = 3
	};


	class InputManager
	{
	public:
		static void Init(GLFWwindow* window);
		static const unsigned int GetKey(keyRef key);

	private:

		static int m_keys[KEY_ARRAY_SIZE];

		static void loadDefaultKeys();

		static GLFWwindow* m_window;

	};

}