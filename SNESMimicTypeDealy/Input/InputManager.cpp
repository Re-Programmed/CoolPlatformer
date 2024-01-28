#include "InputManager.h"
#include "../Settings/AppDataFileManager.h"

namespace GAME_NAME
{

	int InputManager::m_keys[KEY_ARRAY_SIZE];
	GLFWwindow* InputManager::m_window;

	bool InputManager::m_keysDown[KEY_ARRAY_SIZE];

	void InputManager::Init(GLFWwindow* window)
	{
		//LOAD KEY INPUT SETTINGS FROM SAVE

		/*if no keys are saved*/loadDefaultKeys();

		m_window = window;
	}

	/*void InputManager::SetScrollCallback(Window* window, void (*f)(Window*, double, double))
	{
		m_scrollCallback = f;
	}

	void InputManager::ScrollCallback(Window* window, double offsetx, double offsety)
	{
		m_scrollCallback(window, offsetx, offsety);
	}*/

	const unsigned int InputManager::GetKey(keyRef key)
	{
		return glfwGetKey(m_window, m_keys[key]);
	}

	const unsigned int InputManager::GetKey(int key)
	{
		return glfwGetKey(m_window, key);
	}



	const GAME_NAME::InputManager::KEY_STATE InputManager::GetKeyUpDown(keyRef key)
	{
		if (glfwGetKey(m_window, m_keys[key]))
		{
			if(!m_keysDown[key])
			{
				m_keysDown[key] = true;

				return KEY_STATE_PRESSED;
			}

			return KEY_STATE_HELD;
		}

		if (m_keysDown[key])
		{
			m_keysDown[key] = false;
			return KEY_STATE_RELEASED;
		}

		return KEY_STATE_NONE;
	}

	const float InputManager::GetJoystick()
	{

		/*for (int i = 0; i < 16; i++)
		{
			int present = glfwJoystickPresent(i);
			if (present == GLFW_TRUE)
			{
				std::cout << glfwGetJoystickName(i) << std::endl;
				continue;
			}

			break;
		}*/

		int count;
		const float* f = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		//std::cout << glfwGetJoystickName(0) << ": " << count << " == " << f[0] << std::endl;

		for (int i = 0; i < count; i++)
		{
			//if (f[i] == GLFW_PRESS)
			//{
				//std::cout << glfwGetJoystickName(GLFW_JOYSTICK_1) << ": " << i << " == " << f[i] << std::endl;

			//}
		}

		return 0.0f;
	}

	MathUtils::Vec2 InputManager::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		return MathUtils::Vec2(x, y);
		
	}

	MathUtils::Vec2 InputManager::GetMouseScreenPosition()
	{
		MathUtils::Vec2 screenCoords = GetMousePosition();
		int wWidth, wHeight;
		glfwGetWindowSize(m_window, &wWidth, &wHeight);
		MathUtils::Vec2 normalizedScreenCoords = MathUtils::Vec2(screenCoords.X / wWidth, 1 - (screenCoords.Y) / wHeight);

		return MathUtils::Vec2(TargetResolutionX * normalizedScreenCoords.X, TargetResolutionY * normalizedScreenCoords.Y);
	}



	MathUtils::Vec2 InputManager::GetMouseWorldPosition(Rendering::Camera::Camera* camera)
	{
		return GetMouseScreenPosition() + camera->GetPosition();
	}

#define LoadKey(bind, default_k) m_keys[bind] = std::stoi(AppData::AppDataFileManager::GetValue("settings\\keybinds.dat", KeybindNames[bind], std::to_string(default_k)));

	void InputManager::loadDefaultKeys()
	{
		LoadKey(PLAYER_MOVE_UP, GLFW_KEY_W);
		LoadKey(PLAYER_MOVE_DOWN, GLFW_KEY_S);
		LoadKey(PLAYER_MOVE_LEFT, GLFW_KEY_A);
		LoadKey(PLAYER_MOVE_RIGHT, GLFW_KEY_D);

		LoadKey(PLAYER_JUMP, GLFW_KEY_SPACE);

		LoadKey(PLAYER_FORCE_WALK, GLFW_KEY_LEFT_SHIFT);

		LoadKey(PLAYER_INTERACT, GLFW_KEY_E);
#if _DEBUG
		LoadKey(PLAYER_DEBUG, GLFW_KEY_P);

		LoadKey(DEBUG_EDITOR_SELECT, GLFW_KEY_V);

		LoadKey(DEBUG_OBJECT_MENU, GLFW_KEY_TAB);

		LoadKey(PLAYER_DEBUG_ADD_SPEED, GLFW_KEY_LEFT_SHIFT);

		LoadKey(DEBUG_SET_OBJECT_X, GLFW_KEY_X);
		LoadKey(DEBUG_SET_OBJECT_Y, GLFW_KEY_Y);

		LoadKey(DEBUG_REFRESH_LEVEL_FILES, GLFW_KEY_M);
		LoadKey(PLAYER_DEBUG_TOGGLE_FLIGHT, GLFW_KEY_V);
#endif

		//Default Keys (Cannot be changed in settings)
		m_keys[DEFAULT_PAUSE_GAME] = GLFW_KEY_ESCAPE;
	}
}