#pragma once

#include "../Game/Game.h"
#include "../Game/Level.h"
#include "./Objects/Player/Player.h"
#include "./Camera/GameCamera.h"


namespace GAME_NAME
{
	using namespace Objects;
	using namespace Player;

	class TestGame : public Game::Game
	{
	public:
		static std::shared_ptr<Objects::Player::Player> ThePlayer;	//Stores a reference to the player object.

		static TestGame* INSTANCE;									//Singleton.

		void Update(GLFWwindow* window);							//Called every frame before rendering.
		void Init(GLFWwindow* window);								//Called when the program loads.
		void LateUpdate(GLFWwindow* window);						//Called every frame after rendering.

		void InitLevel(GAME_NAME::Game::Level level);				//Called when a new level loads.

	private:
		GAME_NAME::Camera::GameCamera* m_gameCamera;				//Pointer to the camera.
	};
}