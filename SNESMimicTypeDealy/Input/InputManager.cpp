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

	const unsigned int InputManager::GetKey(int key)
	{
		return glfwGetKey(m_window, key);
	}

	MathUtils::Vec2 InputManager::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		return MathUtils::Vec2(x, y);
		
	}

	MathUtils::Vec2 InputManager::GetMouseWorldPosition(Rendering::Camera::Camera* camera)
	{
		MathUtils::Vec2 screenCoords = GetMousePosition();
		int wWidth, wHeight;
		glfwGetWindowSize(m_window, &wWidth, &wHeight);
		MathUtils::Vec2 normalizedScreenCoords = MathUtils::Vec2(screenCoords.X / wWidth, 1 - (screenCoords.Y) / wHeight);
	
		return MathUtils::Vec2(TargetResolutionX * normalizedScreenCoords.X, TargetResolutionY * normalizedScreenCoords.Y) + camera->GetPosition();
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

		m_keys[DEBUG_EDITOR_SELECT] = GLFW_KEY_V;

		m_keys[DEBUG_OBJECT_MENU] = GLFW_KEY_TAB;
#endif
	}
}