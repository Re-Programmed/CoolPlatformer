#include "Tree.h"
#include "../../../../Resources/Save/SaveManager.h"
#include "../../../../Objects/StateSaver.h"
#include "../../../../Input/InputManager.h"

namespace GAME_NAME::Objects::Environment::Plants
{
	Tree::Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, Rendering::Sprite* choppedSprite)
		: GameObject(position, scale, sprite), GameObjectState(saveID),
		m_isChopped(false), m_choppedSprite(choppedSprite)
	{
		LoadState();

	}

	void Tree::SaveState()
	{
		Resources::SaveManager::SaveLevelString(m_isChopped ? "t" : "f", m_objectSaveID);
	}

	void Tree::LoadState()
	{
		std::string result("f");
		Resources::SaveManager::GetLevelString(result, m_objectSaveID);
		setChopped(result.starts_with("t"));
	}

	void Tree::Update(GLFWwindow* window)
	{

	}

	bool Tree::Chop()
	{
		if (m_isChopped) { return false; }

		setChopped(true);

		if (!m_toBeSaved)
		{
			StateSaver::RegisterToBeSaved(this);
		}

		//DROP ITEMS
	}

	void Tree::setChopped(bool chopped)
	{
		if (m_isChopped == chopped) { return; }

		m_isChopped = chopped;

		//FLIP m_choppedSprite and m_sprite
		Rendering::Sprite* spCpy = new Rendering::Sprite(m_choppedSprite->GetSpriteId());

		delete m_choppedSprite;
		this->m_choppedSprite = m_sprite;

		m_sprite = spCpy;
	}
}


