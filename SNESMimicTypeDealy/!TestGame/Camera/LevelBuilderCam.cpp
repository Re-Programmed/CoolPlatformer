#if _DEBUG

#include "LevelBuilderCam.h"

#include "../../Input/InputManager.h"

namespace GAME_NAME::Camera
{
	LevelBuilderCam::LevelBuilderCam(Vec2 pos, float zoom)
	{
		m_position = pos;
		m_zoom = zoom;
	}

	void LevelBuilderCam::Update(const Vec2& playerPos)
	{
		if (InputManager::GetKey(GLFW_KEY_UP))
		{
			m_position += { 0, 0.1f };
		}

		if (InputManager::GetKey(GLFW_KEY_DOWN))
		{
			m_position += { 0, -0.1f };
		}

		if (InputManager::GetKey(GLFW_KEY_LEFT))
		{
			m_position += { -0.1f, 0.f };
		}

		if (InputManager::GetKey(GLFW_KEY_RIGHT))
		{
			m_position += { 0.1f, 0.f };
		}

		if (InputManager::GetKey(GLFW_KEY_I))
		{
			Zoom(0.01f);
		}

		if (InputManager::GetKey(GLFW_KEY_K))
		{
			Zoom(-0.01f);
		}
	}

}

#endif