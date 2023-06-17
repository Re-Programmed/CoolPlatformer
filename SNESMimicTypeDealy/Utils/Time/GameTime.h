#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>
#include "../IUpdateable.h"

namespace GAME_NAME
{
	namespace Utils
	{
		namespace Time
		{
			//Used for getting the amount of time that has passed in each frame, and the time scale that can be used to slow down everything.
			static class GameTime : public IUpdateable
			{
			public:
				
				static class DeltaTime	//Multiply DeltaTime by all your variables that deal with input to prevent weird stuff.
				{
				public:
					static void Update();
					static double GetDeltaTime();
				private:
					static double m_deltaTime;
					static double m_previousTime;

				};

				static double GetScaledDeltaTime();

				static float GetTimeScale();
				static void SetTimeScale(float timeScale);

				void Update(GLFWwindow* window);
			private:
				static float m_timeScale;

				
			};
		}
	}
}