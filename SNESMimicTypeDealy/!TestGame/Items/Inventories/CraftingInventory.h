#pragma once

#include "./InventoryContainer.h"

namespace GAME_NAME::Items::Inventories
{
	class CraftingInventory
		: public InventoryContainer
	{
	public:
		CraftingInventory(std::string name, uint8_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, float rotation, unsigned int recipiesID);

	private:
		const unsigned int m_recipesID;
	};
}