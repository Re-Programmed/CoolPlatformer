#pragma once

#include "../../../Objects/Helpers/Interactable.h"
#include "../../../Objects/GameObjectState.h"

namespace GAME_NAME::Objects::Collectables
{
	class BasicCollectable
		: public Interactable, public GameObjectState
	{
	public:
		BasicCollectable(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveId = 0);

		/// <summary>
		/// Loads this objects state from the current save file.
		/// </summary>
		void LoadState() override;

		/// <summary>
		/// Saves this objects state to the current save file.
		/// </summary>
		void SaveState() override;

	protected:
		void onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state) override;
	};
}