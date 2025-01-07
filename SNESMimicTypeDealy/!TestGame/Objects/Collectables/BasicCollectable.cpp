#include "BasicCollectable.h"

#include "../../../Input/InputManager.h"
#include "../../../Resources/Save/SaveManager.h"

namespace GAME_NAME::Objects::Collectables
{
	BasicCollectable::BasicCollectable(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveId)
		: Interactable(PLAYER_INTERACT, InputManager::KEY_STATE_NONE, scale.X, position, scale, sprite), GameObjectState(saveId)
	{
		LoadState();
	}

	void BasicCollectable::LoadState()
	{
		//Load if this collectable has already been gotten.
		std::string result(SAVE_MNG_FALSE_STATE + "");
		Resources::SaveManager::GetLevelString(result, m_objectSaveID);

		m_isCollected = result.starts_with(SAVE_MNG_TRUE_STATE);
	}

	void BasicCollectable::SaveState()
	{
		std::string saveStr = "";
		saveStr = saveStr + SAVE_MNG_STATE(m_isCollected);

		Resources::SaveManager::SaveLevelString(saveStr, m_objectSaveID);
	}

	void BasicCollectable::Render(const Vec2& cameraPosition)
	{
		//Don't render collected objects.
		if (m_isCollected) { return; }
	}

	void BasicCollectable::onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state)
	{
		if (m_isCollected) { return; }

		//The collectable was collected...

		m_isCollected = true;		   //Set collected.
		SetToBeSaved(true);			   //Prep to save the object.

		onCollect();				   //Callback.
	}

}