#include "MoveableCamera.h"
#include <iostream>

namespace GAME_NAME
{

	namespace Rendering
	{
		namespace Camera
		{
			MoveableCamera* mainMoveableCamera;

			using namespace MathUtils;
			void onScroll(GLFWwindow* window, double xoffset, double yoffset)
			{
				mainMoveableCamera->Zoom((float)yoffset * 0.01f * ZOOM_SPEED);
			}

			MoveableCamera::MoveableCamera()
				: Camera(Vec2::Zero, 1.f), m_speed(5.f)
			{
				mainMoveableCamera = this;
			}

			MoveableCamera::MoveableCamera(GLFWwindow* window, Vec2 position, float zoom, float speed)
				: Camera(position, zoom), m_speed(speed)
			{
				glfwSetScrollCallback(window, onScroll);
				mainMoveableCamera = this;
			}

			void MoveableCamera::Update(GLFWwindow* window)
			{
				if (InputManager::GetKey(PLAYER_MOVE_UP) == GLFW_PRESS)
				{
					Translate(Vec2::OneY * m_speed);
				}

				if (InputManager::GetKey(PLAYER_MOVE_DOWN) == GLFW_PRESS)
				{
					Translate(Vec2::MinusOneY * m_speed);
				}

				if (InputManager::GetKey(PLAYER_MOVE_LEFT) == GLFW_PRESS)
				{
					Translate(Vec2::MinusOneX * m_speed);
				}

				if (InputManager::GetKey(PLAYER_MOVE_RIGHT) == GLFW_PRESS)
				{
					Translate(Vec2::OneX * m_speed);
				}
			}
		}
	}
}