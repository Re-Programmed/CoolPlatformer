#include "CraftingInventory.h"

namespace GAME_NAME::Items::Inventories
{
	CraftingInventory::CraftingInventory(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, float rotation, unsigned int recipiesID)
		: InventoryContainer(name, size, position, scale, sprite, saveID, rotation), m_recipesID(recipiesID)
	{

	}
}
