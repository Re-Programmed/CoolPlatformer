#include "ClimbableObject.h"

namespace GAME_NAME::Objects::Environment
{
	ClimbableObject::ClimbableObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite)
		: Interactable(PLAYER_MOVE_UP, InputManager::KEY_STATE_PRESSED, position, scale, sprite, 0.f, true)
	{

	}

	void ClimbableObject::onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state)
	{
		if (player->GetClimbing()) { return; }
		player->SetClimbing(this);
	}
}

