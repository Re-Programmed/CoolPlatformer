#pragma once

#include "../Game/Game.h"
#include "../Game/Level.h"
#include "./Objects/Player/Player.h"
#include "./Camera/GameCamera.h"
#include "Level/GlobalLevelData.h"


namespace GAME_NAME
{
	using namespace Objects;
	using namespace Player;
	using namespace Level;

	class TestGame : public Game::Game
	{
	public:
		static std::shared_ptr<Objects::Player::Player> ThePlayer;	//Stores a reference to the player object.

		static TestGame* INSTANCE;									//Singleton.

		void Update(GLFWwindow* window);							//Called every frame before rendering.
		void Init(GLFWwindow* window);								//Called when the program loads.
		void LateUpdate(GLFWwindow* window);						//Called every frame after rendering.

		void InitLevel(GAME_NAME::Game::Level level);				//Called when a new level loads.

		static GLFWwindow* FirstWindow;

		/// <summary>
		/// Returns true if the game is paused.
		/// </summary>
		inline static bool GetGamePaused()
		{
			return m_gamePaused;
		}

		static void TogglePauseState();

		/// <summary>
		/// Retuns a pointer to the current level's global level data.
		/// </summary>
		/// <returns></returns>
		static inline GlobalLevelData* GetGlobalLevelData()
		{
			return m_globalLevelData;
		}
	private:
		GAME_NAME::Camera::GameCamera* m_gameCamera;				//Pointer to the camera.

		/// <summary>
		/// Global Level Data for the current level.
		/// </summary>
		static GlobalLevelData* m_globalLevelData;
		
		/// <summary>
		/// True if the game is paused.
		/// </summary>
		static bool m_gamePaused;

	};
}