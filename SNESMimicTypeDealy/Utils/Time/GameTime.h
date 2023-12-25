#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <functional>
#include "../IUpdateable.h"

#ifndef _GAME_TIME_DEF
#define _GAME_TIME_DEF

namespace GAME_NAME::Utils::Time
{
	//Used for getting the amount of time that has passed in each frame, and the time scale that can be used to slow down everything.
	class GameTime
	{
	public:

		class DeltaTime	//Multiply DeltaTime by all your variables that deal with things not reliant on frame rate.
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

		static double GetElapsedTime();

		static void Update();
	private:
		static float m_timeScale;
	};
}


#endif