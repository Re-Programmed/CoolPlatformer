#pragma once
#include "../Utils/Math/Vec2.h"
#include "../Utils/Math/Vec4.h"
#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera/Camera.h"
#include "Camera/MoveableCamera.h"

namespace GAME_NAME
{

	using namespace Rendering;
	using namespace MathUtils;
	class Window
	{
	public:
		GLFWwindow* GetWindow();
		Camera::Camera* GetCamera();

		Window(bool fullscreen);
		~Window();

		void Render();
		/// <summary>
		/// Returns if the window should close.
		/// </summary>
		bool ShouldClose();
		/// <summary>
		/// Sets if the window should be displayed in fullscreen or windowed mode.
		/// </summary>
		void SetFullscreen(bool fullscreen);
		/// <summary>
		/// Sets the clear color for the window.
		/// </summary>
		void SetClearColor(Vec4 color);

	private:
		GLFWwindow* m_glWindow;
		GAME_NAME::Rendering::Camera::Camera* m_gameCamera;

		bool m_fullscreen;

		void update();
		void lateUpdate();
	};

}