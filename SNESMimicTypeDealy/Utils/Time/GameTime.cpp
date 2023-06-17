#include "GameTime.h"
#include <iostream>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>

namespace GAME_NAME
{
	namespace Utils
	{
		namespace Time
		{
#pragma region DeltaTime

			double GameTime::DeltaTime::m_previousTime = 0;
			double GameTime::DeltaTime::m_deltaTime = 0;

			double GameTime::DeltaTime::GetDeltaTime()
			{
				return m_deltaTime;
			}

			double GameTime::GetScaledDeltaTime()
			{
				return DeltaTime::GetDeltaTime() * m_timeScale;
			}

			void GameTime::DeltaTime::Update()
			{
				double time = glfwGetTime();
				m_deltaTime = time - m_previousTime;
				m_previousTime = time;
			}

#pragma endregion

			float GameTime::m_timeScale = 1.f;

			float GameTime::GetTimeScale()
			{
				return m_timeScale;
			}

			void GameTime::SetTimeScale(float timeScale)
			{
				m_timeScale = timeScale;
			}

			void GameTime::Update(GLFWwindow* window)
			{
				DeltaTime::Update();
			}
		}
	}
}
