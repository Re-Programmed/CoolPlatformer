#include "InputManager.h"

namespace GAME_NAME
{

	int InputManager::m_keys[KEY_ARRAY_SIZE];
	GLFWwindow* InputManager::m_window;

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

	void InputManager::loadDefaultKeys()
	{
		m_keys[0] = GLFW_KEY_W;
		m_keys[1] = GLFW_KEY_S;
		m_keys[2] = GLFW_KEY_A;
		m_keys[3] = GLFW_KEY_D;

		m_keys[PLAYER_JUMP] = GLFW_KEY_SPACE;

#if _DEBUG
		m_keys[PLAYER_DEBUG] = GLFW_KEY_P;
#endif
	}
}