#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include "../Rendering/Window.h"

///How many inputs to check for
#if _DEBUG
#define KEY_ARRAY_SIZE 6
#else
#define KEY_ARRAY_SIZE 5
#endif

namespace GAME_NAME
{
	//Key codes.
	enum keyRef
	{
									//    --NAME--   [DEFAULT]
		PLAYER_MOVE_UP = 0,			//Player Move Up [W]
		PLAYER_MOVE_DOWN = 1,		//Player Move Down [S]
		PLAYER_MOVE_LEFT = 2,		//Player Move Left [A]
		PLAYER_MOVE_RIGHT = 3,		//Player Move Right [D]
		PLAYER_JUMP,				//Player Jump [Space]




#if _DEBUG
		PLAYER_DEBUG				//Player Enter Debug Mode [P]
#endif
	};


	//Deals with input. Input buttons can be changed using the m_keys array allowing for adjustable inputs.
	class InputManager
	{
	public:
		static void Init(GLFWwindow* window);			//Must be called on program start.
		static const unsigned int GetKey(keyRef key);	//Gets if a key is down.

	private:

		static int m_keys[KEY_ARRAY_SIZE];				//Determines what button each keyRef refers to.

		static void loadDefaultKeys();					//Loads the default inputs for keyboard.

		static GLFWwindow* m_window;					//Window pointer. :)

	};

}