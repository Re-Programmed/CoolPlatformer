#pragma once
#include "../../../../Objects/Helpers/Interactable.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	class Bench
		: public Interactable
	{
	public:
		Bench(Vec2 position, Vec2 scale, Sprite* sprite);

	protected:
		void onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state) override;
	};
}