#pragma once
#include "../Utils/Math/Vec2.h"
#include "../Utils/Math/Vec4.h"
#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Camera/Camera.h"
#include "Camera/MoveableCamera.h"
#include "../Game/Game.h"

namespace GAME_NAME
{
	using namespace Rendering;
	using namespace MathUtils;

	typedef Vec4 Color;

	class Window	//The game window.
	{
	public:
		GLFWwindow* GetWindow();

		Window(bool fullscreen, GAME_NAME::Game::Game* game);
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
		void SetClearColor(Color color);


	private:
		GAME_NAME::Game::Game* const m_game;	//The current game.

		GLFWwindow* m_glWindow;					//The current GLFW window.

		bool m_fullscreen;						//Is the window fullscreen?

		void update();
		void lateUpdate();
	};

}