#include "IntroductionLevelManager.h"

#include "../../TestGame.h"

namespace GAME_NAME::Level
{
	IntroductionLevelManager::IntroductionLevelManager()
	{
		TestGame::ThePlayer->HideAllUI();
		TestGame::INSTANCE->GetCamera()->SetPosition(TestGame::ThePlayer->GetPosition() - Vec2{ TargetResolutionX, TargetResolutionY } / 2.f);
	}

	void IntroductionLevelManager::Update(GLFWwindow* window)
	{

	}
}

