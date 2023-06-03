#include "Window.h"
#include <cstdlib>
#include <iostream>
#include "./BufferManager.h"
#include "./Renderers/Renderer.h"
#include "./Sprite.h"
#include "../Objects/GameObject.h"
#include "../Resources/AssetManager.h"
#include "../Input/InputManager.h"

namespace GAME_NAME
{
	Vec2* lastWindowSize;

	void windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glOrtho(0, width, 0, height, 0, 100);
		glMatrixMode(GL_MODELVIEW);

		lastWindowSize = new Vec2(width, height);
	}

	GLFWwindow* Window::GetWindow()
	{
		return m_glWindow;
	}

	Camera::Camera* Window::GetCamera()
	{
		return m_gameCamera;
	}

	Window::Window(bool fullscreen) : m_fullscreen(fullscreen), m_gameCamera(new Camera::MoveableCamera())
	{
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

		int width, height;
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		width = mode->width;
		height = mode->height;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		this->m_glWindow = glfwCreateWindow(width, height, "SMW platformer type game", fullscreen ? primaryMonitor : NULL, NULL);

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

		windowSizeCallback(m_glWindow, width, height);

		Sprite::SetResolution(Vec2(width, height));

		//glMatrixMode(GL_PROJECTION);
		//glOrtho(0, width, 0, height, 0, 100);
		//glMatrixMode(GL_MODELVIEW);

		BufferManager::GenBuffers();

		InputManager::Init(m_glWindow);


		//TEST?

		///CHUNK DATA HAS BACKGROUND INFO (THIS NEEDS CHANGED BECAUSE THE CHUNKS OBJECTS NEED PARALLAX!)
		std::vector<int> cd = Resources::AssetManager::GetChunkData("/testing");
		
		Renderer::InitChunks(cd);

		m_gameCamera = new Camera::MoveableCamera(m_glWindow, Vec2::Zero, 1.f, 10.f);

		Resources::AssetManager::LoadTextures("/testing");

		GameObject obj[2];

		///CHUNK OBJECTS ARE STATIC OBJECTS
		obj[0] = GameObject(Vec2::Zero, Vec2(100, 100), Renderer::GetSprite(1));
		obj[1] = GameObject(Vec2(550, 550), Vec2(100, 100), Renderer::GetSprite(2));

		Renderer::LoadObjects(obj, 2);


		///WHAT ABOUT MOVING OBJECTS THAT EXCEED CHUNKS LIKE ENEMIES AND THE PLAYER!!!!! (WE CANT KEEP UPDATING WHAT CHUNK THEY ARE IN, WE NEED TO SPECIFICALLY CHECK THEIR POSITION)
	}

	Window::~Window()
	{
		glfwDestroyWindow(this->m_glWindow);
	}

	void Window::Render()
	{
		update();

		glClear(GL_COLOR_BUFFER_BIT);

		//Draw Color
		//glColor3f(1, 0, 0);

		Renderer::Render(m_gameCamera, lastWindowSize, RENDER_LAYER_BG, 2.f);
		Renderer::Render(m_gameCamera, lastWindowSize, RENDER_LAYER_OBJECTS);

		glfwSwapBuffers(this->m_glWindow);
		glfwPollEvents();

		lateUpdate();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(this->m_glWindow);
	}


	void Window::SetFullscreen(bool fullscreen)
	{
		this->m_fullscreen = fullscreen;

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowMonitor(m_glWindow, fullscreen ? glfwGetPrimaryMonitor() : NULL, 0, 0, mode->width, mode->height, mode->refreshRate);

		windowSizeCallback(m_glWindow, mode->width, mode->height);
	}

	void Window::SetClearColor(Vec4 color)
	{
		glClearColor(color.X, color.Y, color.Z, color.W);
	}


	void Window::update()
	{
		m_gameCamera->Update(m_glWindow);
	}

	void Window::lateUpdate()
	{

	}
}