#pragma once

#include "../Inventory.h"
#include "../../../Objects/GameObject.h"
#include "../../../Objects/Helpers/Interactable.h"
#include "../../Objects/Player/Player.h"

#define OPEN_INVENTORY_CONTAINER_KEY keyRef::PLAYER_INTERACT

namespace GAME_NAME::Items::Inventories
{
	class InventoryContainer
		: public Inventory, public Interactable
	{
	public:
		InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation = 0.f);
		InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation, int itemCount, ...);

		void OpenGUI();
		void CloseGUI();

		void Update(GLFWwindow* window) override;

		void onInteract(std::shared_ptr<GAME_NAME::Objects::Player::Player> player, InputManager::KEY_STATE state) override;

		inline bool GetOpen()
		{
			return m_isOpen;
		}
	private:
		bool m_isOpen = false;
	};
}