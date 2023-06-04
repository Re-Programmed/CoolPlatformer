#pragma once

#include "../Game/Game.h"

namespace GAME_NAME
{
	class TestGame : public Game::Game
	{
	public:
		void Update(GLFWwindow* window);
		void Init(GLFWwindow* window);
		void LateUpdate(GLFWwindow* window);
	};
}