#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
//#include "../Rendering/Window.h"
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Camera/Camera.h"
#include "../Rendering/Sprite.h"
#include <vector>

///How many inputs to check for
#if _DEBUG
#define KEY_ARRAY_SIZE 15
#else
#define KEY_ARRAY_SIZE 7
#endif

const std::string KeybindNames[KEY_ARRAY_SIZE] {
	"PLAYER_MOVE_UP",
	"PLAYER_MOVE_DOWN",
	"PLAYER_MOVE_LEFT",
	"PLAYER_MOVE_RIGHT",
	"PLAYER_JUMP",
	"PLAYER_FORCE_WALK",
	"DEFAULT_PAUSE_GAME",
#if _DEBUG
	"PLAYER_DEBUG",
	"DEBUG_EDITOR_SELECT",
	"DEBUG_OBJECT_MENU",
	"PLAYER_DEBUG_ADD_SPEED",
	"DEBUG_SET_OBJECT_X",
	"DEBUG_SET_OBJECT_Y",
	"DEBUG_REFRESH_LEVEL_FILES",
	"PLAYER_DEBUG_TOGGLE_FLIGHT"
#endif
};

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

		DEFAULT_PAUSE_GAME,			//Pause Game {DEFAULT} [ESC]

#if _DEBUG
		PLAYER_DEBUG,				//Player Enter Debug Mode [P]
		DEBUG_EDITOR_SELECT,		//Select an object in the editor [V]
		DEBUG_OBJECT_MENU,			//Open the object menu [Tab]
		PLAYER_DEBUG_ADD_SPEED,		//Make the player move faster while flying around [Shift]
		DEBUG_SET_OBJECT_X,			//Pressed to set the X position of an object by typing [X]
		DEBUG_SET_OBJECT_Y,			//Pressed to set the Y position of an object by typing [Y]
		DEBUG_REFRESH_LEVEL_FILES,	//Pressed to reload the current level with any updates. [M]
		PLAYER_DEBUG_TOGGLE_FLIGHT	//Pressed to toggle flying [V]
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

		const enum KEY_STATE
		{
			KEY_STATE_NONE = 0b0001,
			KEY_STATE_PRESSED = 0b0010,
			KEY_STATE_RELEASED = 0b0100,
			KEY_STATE_HELD = 0b1000
		};

		//Returns KEY_STATE_PRESSED if the key was just pressed, KEY_STATE_RELEASED if the key was just released, KEY_STATE_HELD if the key is held, and KEY_STATE_NONE if the key is not pressed.
		static const KEY_STATE GetKeyUpDown(keyRef key);

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

		static bool m_keysDown[KEY_ARRAY_SIZE];			//Stores which keys are held.
	};

}