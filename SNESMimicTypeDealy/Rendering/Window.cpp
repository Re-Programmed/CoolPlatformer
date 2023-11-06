#include "Window.h"
#include <cstdlib>
#include <iostream>
#include "./BufferManager.h"
#include "./Renderers/Renderer.h"
#include "./Sprite.h"
#include "../Objects/GameObject.h"
#include "../Resources/AssetManager.h"
#include "../Input/InputManager.h"
#include "../Utils/UpdateManager.h"
#if _DEBUG
#include "../Debug/DebugLog.h"
#endif
#include "../Audio/SoundManager.h"

namespace GAME_NAME
{
	Vec2* lastWindowSize;


	void windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (width == 0 || height == 0) {
			return;
		}

		float adjustedWindowW = (float)height * (FORCE_WINDOW_RATIO_X / FORCE_WINDOW_RATIO_Y);
		float adjustedWindowH = (float)width * (FORCE_WINDOW_RATIO_Y / FORCE_WINDOW_RATIO_X);

		if (lastWindowSize != nullptr && lastWindowSize->X != width)
		{
			glfwSetWindowSize(window, width, adjustedWindowH);
		}
		else {
			glfwSetWindowSize(window, adjustedWindowW, height);
		}

		lastWindowSize = new Vec2(width, height);

		Sprite::SetResolution(Vec2(width, height));
	}

	GLFWwindow* Window::GetWindow()
	{
		return m_glWindow;
	}


	Window::Window(bool fullscreen, GAME_NAME::Game::Game* game) : m_game(game), m_fullscreen(fullscreen)
	{
		/*----------------------
			ADD INITS
		------------------------*/

		int count;
		GLFWmonitor* primaryMonitor = glfwGetMonitors(&count)[count - 1]; //Change later to choose a monitor.
		
		int width, height;
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		width = mode->width;
		height = mode->height;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //DISABLE RESIZING

		std::string title = "SMW platformer type game";
		this->m_glWindow = glfwCreateWindow(width, height, title.c_str(), fullscreen ? primaryMonitor : NULL, NULL);
		#if _DEBUG
		DEBUG::DebugLog::Log("Created Window: " + title + "\n", true, ";1;4");
		#endif

		if (!this->m_glWindow)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwMakeContextCurrent(this->m_glWindow);
		gladLoadGL();

		glfwSetWindowSizeCallback(m_glWindow, windowSizeCallback);

		//glViewport(0, 0, width, height);

		glEnable(GL_TEXTURE_2D);

		//BLENDING
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glOrtho(0, width, 0, height, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		windowSizeCallback(m_glWindow, width, height);
		glfwSetWindowSizeLimits(m_glWindow, 200, 200, GLFW_DONT_CARE, GLFW_DONT_CARE);

		//glMatrixMode(GL_PROJECTION);
		//glOrtho(0, width, 0, height, 0, 100);
		//glMatrixMode(GL_MODELVIEW);

		BufferManager::GenBuffers();

		InputManager::Init(m_glWindow);

		Audio::SoundManager::Init();

		m_game->Init(m_glWindow); //INITILIZE GAME LAST

		//TEST?

		///CHUNK DATA HAS BACKGROUND INFO (THIS NEEDS CHANGED BECAUSE THE CHUNKS OBJECTS NEED PARALLAX!)
		
		///WHAT ABOUT MOVING OBJECTS THAT EXCEED CHUNKS LIKE ENEMIES AND THE PLAYER!!!!! (WE CANT KEEP UPDATING WHAT CHUNK THEY ARE IN, WE NEED TO SPECIFICALLY CHECK THEIR POSITION)
	}

	Window::~Window()
	{
		Audio::SoundManager::DeInit();

		glfwDestroyWindow(this->m_glWindow);
	}


	void Window::Render()
	{
		update();

		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Color
		//glColor3f(1, 0, 0);

		Renderer::Render(m_game->GetCamera(), lastWindowSize, RENDER_LAYER_BG, m_glWindow, 2.f);
		Renderer::Render(m_game->GetCamera(), lastWindowSize, RENDER_LAYER_OBJECTS, m_glWindow);
		Renderer::Render(m_game->GetCamera(), lastWindowSize, RENDER_LAYER_ACTIVE_OBJECTS, m_glWindow);

		if (m_game->RenderFront)
		{
			Renderer::Render(m_game->GetCamera(), lastWindowSize, RENDER_LAYER_OBJECTS_FRONT, m_glWindow);
		}

		Renderer::Render(m_game->GetCamera(), lastWindowSize, RENDER_LAYER_GUI, m_glWindow);

		glfwSwapBuffers(this->m_glWindow);
		glfwPollEvents();

		lateUpdate();
	}

	void Window::SetFullscreen(bool fullscreen)
	{
		this->m_fullscreen = fullscreen;

		int count;
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetMonitors(&count)[count - 1] /*Change later to choose a monitor.*/);
		int mWidth, mHeight, mPosX, mPosY;
		int wWidth = mode->width - INITIAL_WINDOW_FULLSCREEN_OFF_PADDING_X;
		int wHeight = mode->height - INITIAL_WINDOW_FULLSCREEN_OFF_PADDING_Y;
		glfwGetMonitorWorkarea(glfwGetMonitors(&count)[count - 1] /*Change later to choose a monitor.*/, &mPosX, &mPosY, &mWidth, &mHeight);
		glfwSetWindowMonitor(m_glWindow, fullscreen ? glfwGetMonitors(&count)[count - 1] : NULL, mWidth/2 - wWidth/2 + mPosX, mHeight/2 - wHeight/2 + mPosY + INITIAL_WINDOW_FULLSCREEN_OFF_OFFSET_Y, wWidth, wHeight, mode->refreshRate);

		windowSizeCallback(m_glWindow, mode->width, mode->height);

		glfwSetWindowAttrib(m_glWindow, GLFW_RESIZABLE, m_fullscreen ? GLFW_FALSE : GLFW_TRUE);

	}

	void Window::SetClearColor(Color color)
	{
		glClearColor(color.X, color.Y, color.Z, color.W);
	}

	bool F11press = false;
	void Window::update()
	{
		if (glfwGetKey(m_glWindow, GLFW_KEY_F11))
		{
			if (!F11press)
			{
				std::cout << "UPDATING" << std::endl;
				F11press = true;

				SetFullscreen(!this->m_fullscreen);
			}
		}
		else {
			F11press = false;
		}

		GAME_NAME::Utils::UpdateManager::Update(m_glWindow);
	}

	void Window::lateUpdate()
	{

	}
}