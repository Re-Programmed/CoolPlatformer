#if _DEBUG

#pragma once
#include "../../Game/Game.h"

namespace GAME_NAME::Debug::LevelBuilder
{
	class LevelBuilder : public IUpdateable
	{
	public:
		static void InitLevelBuilder(GAME_NAME::Game::Game* game);
		static void InitLevelBuilderAssets(GAME_NAME::Game::Game* game);

		void Update(GLFWwindow* window);
		static void Render();
		static void DestroyLevelBuilder();

		static void DrawObjectMenu();

		LevelBuilder(Game::Game* game, unsigned int loadedSpriteCount)
			:m_updateIndex(UpdateManager::RegisterUpdateable(this)), m_currentGame(game), m_loadedSpriteCount(loadedSpriteCount)
		{
			m_currentLevelBuilder = this;
		}

		~LevelBuilder()
		{
			//if (m_currentGame != nullptr) { delete m_currentGame; }
			if (m_editObject != nullptr)
			{
				delete m_editObject;
			}
		}
	private:
		//The number of sprites that were available upon opening the level editor.
		unsigned int m_loadedSpriteCount;

		bool m_interactKeyDown;

		static bool m_objectMenuOpen;

		GameObject* m_editObject;

		const UpdateIndex m_updateIndex;

		Game::Game* m_currentGame;

		static LevelBuilder* m_currentLevelBuilder;
	};
}

#endif