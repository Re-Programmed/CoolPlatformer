#include "GameTime.h"
#include <iostream>
#include <GLFW/glfw3.h>

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
				std::cout << DeltaTime::GetDeltaTime() << std::endl;
				DeltaTime::Update();
			}
		}
	}
}
