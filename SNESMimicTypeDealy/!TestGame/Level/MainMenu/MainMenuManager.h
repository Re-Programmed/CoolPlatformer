#pragma once
#include "../LevelSystem.h"

#include "../../../Objects/GameObject.h"

#include "../../Objects/Player/Player.h"

#include <array>

namespace GAME_NAME::Level
{
	class MainMenuManager
		: public LevelSystem
	{
	public:
		MainMenuManager();

		void Update(GLFWwindow* window) override;


	private:
		void triggeerTransitionEvent(const Vec2& playerPosition);
		
		static int m_eventIndex;

		bool m_reverseCam = false;

		Objects::Player::Player* m_fakePlayer;
			
		static void buttonCallback(int buttonId);
	};
}