#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include "../Rendering/Window.h"
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Camera/Camera.h"
#include "../Rendering/Sprite.h"

///How many inputs to check for
#if _DEBUG
#define KEY_ARRAY_SIZE 11
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
		PLAYER_FORCE_WALK,			//Player Walk [Shift]



#if _DEBUG
		PLAYER_DEBUG,				//Player Enter Debug Mode [P]
		DEBUG_EDITOR_SELECT,		//Select an object in the editor [V]
		DEBUG_OBJECT_MENU,			//Open the object menu [Tab]
		PLAYER_DEBUG_ADD_SPEED,		//Make the player move faster while flying around [Shift]
		DEBUG_SET_OBJECT_X,			//Pressed to set the X position of an object by typing [X]
		DEBUG_SET_OBJECT_Y			//Pressed to set the Y position of an object by typing [Y]
#endif
	};

	enum joyAxis
	{
		JOY_AXIS_X,
		JOY_AXIS_Y
	};


	//Deals with input. Input buttons can be changed using the m_keys array allowing for adjustable inputs.
	class InputManager
	{
	public:
		static void Init(GLFWwindow* window);			//Must be called on program start.
		static const unsigned int GetKey(keyRef key);	//Gets if a key is down using its alias.
		static const unsigned int GetKey(int key);	//Gets if a key is down using its GLFW key code.

		static const float GetJoystick();

		//Gets the current state of a mouse button.
		static inline const int GetMouseButton(int button)
		{
			return glfwGetMouseButton(m_window, button);
		}

		//Gets the mouse position in screen coordinates.
		static MathUtils::Vec2 GetMousePosition();

		//Gets the mouse position in world coordinates.
		static MathUtils::Vec2 GetMouseScreenPosition();

		//Gets the mouse position in world coordinates with respect to the given camera.
		static MathUtils::Vec2 GetMouseWorldPosition(Rendering::Camera::Camera* camera);

	private:

		static int m_keys[KEY_ARRAY_SIZE];				//Determines what button each keyRef refers to.

		static void loadDefaultKeys();					//Loads the default inputs for keyboard.

		static GLFWwindow* m_window;					//Window pointer. :)
	};

}