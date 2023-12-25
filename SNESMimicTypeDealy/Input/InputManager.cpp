#include "InputManager.h"

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



	const unsigned int InputManager::GetKeyUpDown(keyRef key)
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

	void InputManager::loadDefaultKeys()
	{
		m_keys[0] = GLFW_KEY_W;
		m_keys[1] = GLFW_KEY_S;
		m_keys[2] = GLFW_KEY_A;
		m_keys[3] = GLFW_KEY_D;

		m_keys[PLAYER_JUMP] = GLFW_KEY_SPACE;

		m_keys[PLAYER_FORCE_WALK] = GLFW_KEY_LEFT_SHIFT;

#if _DEBUG
		m_keys[PLAYER_DEBUG] = GLFW_KEY_P;

		m_keys[DEBUG_EDITOR_SELECT] = GLFW_KEY_V;

		m_keys[DEBUG_OBJECT_MENU] = GLFW_KEY_TAB;

		m_keys[PLAYER_DEBUG_ADD_SPEED] = GLFW_KEY_LEFT_SHIFT;

		m_keys[DEBUG_SET_OBJECT_X] = GLFW_KEY_X;
		m_keys[DEBUG_SET_OBJECT_Y] = GLFW_KEY_Y;

		m_keys[DEBUG_REFRESH_LEVEL_FILES] = GLFW_KEY_M;
		m_keys[PLAYER_DEBUG_TOGGLE_FLIGHT] = GLFW_KEY_V;
#endif
	}
}