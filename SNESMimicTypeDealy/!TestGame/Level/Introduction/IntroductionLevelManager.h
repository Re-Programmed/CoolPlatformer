#pragma once
#include "../LevelSystem.h"

namespace GAME_NAME::Level
{
	class IntroductionLevelManager
		: public LevelSystem
	{
	public:
		IntroductionLevelManager();

		void Update(GLFWwindow* window) override;

	};
}