#include "MainMenuManager.h"

#include "../../../Utils/Time/GameTime.h"
#include "../../../Rendering/Renderers/Renderer.h"

#include "../../TestGame.h"

#include "../../../Objects/GUI/Menus/GUIMenu.h"

#include "../../Objects/Environment/ExplosiveObject.h"

#include "../../Camera/GameCamera.h"

#include "../LevelManager.h"

float SCROLL_SPEED = 45.f;

namespace GAME_NAME::Level
{
	int MainMenuManager::m_eventIndex = 0;
	bool transitionTriggered = false;

	MainMenuManager::MainMenuManager()
	{
		GUI::Menus::GUIMenu::LoadMenu("/main_menu", new std::function<void(int)>(MainMenuManager::buttonCallback));
		transitionTriggered = false;
	}


	void MainMenuManager::Update(GLFWwindow* window)
	{
		if (LevelManager::GetCircleAnimationCompleted())
		{
			LevelManager::SetCircleAnimationCompleted(false);

			//Load main level area or whatever.
			//[Continue Game]

			LevelManager::LoadLevelData("/introduction", true);
			LevelManager::LevelCircleAnimation(Vec2{ -1.f }, true);

			return;
		}

		Vec2 translation = { (m_reverseCam ? -1.f : 1.f) * SCROLL_SPEED * (float)Time::GameTime::GetScaledDeltaTime(), 0.f };

		float cameraPosX = TestGame::INSTANCE->GetCamera()->GetPosition().X;

		if (m_eventIndex == 1)
		{
			if (SCROLL_SPEED > 0.f)
			{
				SCROLL_SPEED -= 0.33f;
			}
			else {
				SCROLL_SPEED = 0.f;
			}

			if (m_fakePlayer == nullptr)
			{
				m_fakePlayer = new Objects::Player::Player({ (cameraPosX - 32.f < 1) ? 15 : (cameraPosX - 32.f), 21.f});
				//Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_fakePlayer, true, 1, false));

				Renderer::LoadActiveObject(m_fakePlayer, 1);

				//m_fakePlayer->SetFrozen(true);
			}		

			Vec2 target = Vec2{ cameraPosX + TargetResolutionX / 2, 21.f };

			m_fakePlayer->ClearTargetEvents();
			if (target.X > 0 && std::abs(m_fakePlayer->GetPosition().X - target.X) > 55.f)
			{
				m_fakePlayer->QueueTargetEvent(Objects::Player::Player::TargetEvent(target, true, true, 0.0));
			}
			else if(!transitionTriggered) {
				if (m_fakePlayer->GetVelocity().X < 0.1f)
				{
					transitionTriggered = true;

					triggeerTransitionEvent(m_fakePlayer->GetPosition());
				}
			}
		}
		else if (m_eventIndex == 1000)
		{
			LevelManager::LevelCircleAnimation(Vec2{ TargetResolutionX / 2.f, m_fakePlayer->GetPosition().Y + m_fakePlayer->GetScale().Y/2.f }, false, false);
			m_eventIndex = 0;
		}

		TestGame::INSTANCE->GetCamera()->Translate(translation);

		if (TestGame::INSTANCE->GetCamera()->GetPosition().X >= 2500)
		{
			m_reverseCam = true;
		}

		if (m_reverseCam && TestGame::INSTANCE->GetCamera()->GetPosition().X < ChunkShift)
		{
			m_reverseCam = false;
		}
	}

	void MainMenuManager::triggeerTransitionEvent(const Vec2& playerPosition)
	{
		std::srand(glfwGetTime());

		int randEvent = (std::rand() * 1) / RAND_MAX;

		dynamic_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->LockCamera(playerPosition);
		TestGame::ThePlayer = std::shared_ptr<Objects::Player::Player>(m_fakePlayer);

		switch (randEvent)
		{
		case 0:
			{
			//Explosion from sky.
			std::thread eventThread([playerPosition]() {
				//std::this_thread::sleep_for(std::chrono::milliseconds(500));
				Objects::Environment::ExplosiveObject* eo = new Objects::Environment::ExplosiveObject(Vec2{ playerPosition.X, TargetResolutionY + 21.f }, { 8.f, 12.f }, Renderer::GetSprite(15), 60.f, 25.f, Objects::Environment::ExplosiveObject::JUMPED_ON, 0);
				Renderer::InstantiateObject(Renderer::InstantiateGameObject(eo, true, 1, false));

				for (int i = 0; i < TargetResolutionY; i++)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(3));

					eo->Translate(Vec2{ 0.f, -1.f });
				}

				eo->Explode();

				m_eventIndex = 1000;
			});

			eventThread.detach();
			break;

			}
		}
	}

	void MainMenuManager::buttonCallback(int buttonId)
	{
		m_eventIndex = buttonId + 1;
	}

	/*
	2,%1,0,32,21,6
   ;0,%1|4+,23,32,6,101,0
   ;0,%1|2+,22,32,6,100,1
   ;0,%1,21,32,4,12,3
	*/

}
