#include "InnerThoughtScene.h"
#include "../TestGame.h"
#include "../Camera/GameCamera.h"
#include "../../Objects/GUI/GUIManager.h"
#include <iostream>

namespace GAME_NAME::Cutscenes
{
	InnerThoughtScene::InnerThoughtScene(Vec2 position, float triggerDistance, std::string text)
		: Cutscene(position, triggerDistance), m_text(text)
	{

	}
	bool InnerThoughtScene::Trigger()
	{
		GAME_NAME::TestGame::ThePlayer->SetFrozen(true);

		//Zoom camera in.
		static_cast<GAME_NAME::Camera::GameCamera*>(GAME_NAME::TestGame::INSTANCE->GetCamera())->SetTargetZoom(4.5f);
		static_cast<GAME_NAME::Camera::GameCamera*>(GAME_NAME::TestGame::INSTANCE->GetCamera())->SetOffset({ 17.f, 24.f });

		//Disable all GUI.
		GUI::GUIManager::MenuIsOpen = false;

		std::cout << "CUTSCENE " + this->m_text + "\n";
		return true;
	}
}