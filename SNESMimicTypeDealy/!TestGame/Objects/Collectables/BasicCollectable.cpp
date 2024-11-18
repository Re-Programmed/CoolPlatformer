#include "BasicCollectable.h"

#include "../../../Input/InputManager.h"

namespace GAME_NAME::Objects::Collectables
{
	BasicCollectable::BasicCollectable(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveId)
		: Interactable(PLAYER_INTERACT, InputManager::KEY_STATE_NONE, scale.X, position, scale, sprite), GameObjectState(saveId)
	{

	}

	void BasicCollectable::LoadState()
	{
		//Load if this collectable has already been gotten.
	}

	void BasicCollectable::SaveState()
	{

	}

	void BasicCollectable::onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state)
	{
		//The collectable was collected...

		Renderer::DestroyObject(this); //Destroys and deletes the object.
	}

}