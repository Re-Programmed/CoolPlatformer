#include "Tree.h"
#include "../../../../Resources/Save/SaveManager.h"
#include "../../../../Objects/StateSaver.h"
#include "../../../../Input/InputManager.h"

#define TREE_IS_CHOPPED_ID m_objectSaveID + "_is_chopped"

namespace GAME_NAME::Objects::Environment::Plants
{
	Tree::Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite)
		: GameObject(position, scale, sprite), GameObjectState(std::to_string(position.X) + "," + std::to_string(position.Y) + "tree"),
		m_isChopped(false)
	{
		LoadState();

	}

	void Tree::SaveState()
	{
		Resources::SaveManager::SaveBool(m_isChopped, TREE_IS_CHOPPED_ID);
	}

	void Tree::LoadState()
	{
		Resources::SaveManager::GetSaveBool(TREE_IS_CHOPPED_ID, m_isChopped);
		std::cout << "CHOPPED: " << m_isChopped << std::endl;

		StateSaver::RegisterToBeSaved(this);

	}

	void Tree::Update(GLFWwindow* window)
	{
		if (InputManager::GetKeyUpDown(PLAYER_FORCE_WALK) & InputManager::KEY_STATE_PRESSED)
		{
			m_isChopped = true;
			StateSaver::SaveStates();	
		}
	}
}


