#include "Bench.h"
#include "../../../../Input/InputManager.h"
#include "../../Player/Player.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	Bench::Bench(Vec2 position, Vec2 scale, Sprite* sprite)
		: Interactable(PLAYER_INTERACT, GAME_NAME::InputManager::KEY_STATE_PRESSED, position, scale, sprite)
	{

	}

	void Bench::onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state)
	{
		if (player->GetVelocity().X < 7)
		{
			player->SetFrozen(true, Player::Player::SITTING_FORWARD);
		}
	}
}
