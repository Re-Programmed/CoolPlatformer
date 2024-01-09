#include "Inventory.h"

namespace GAME_NAME::Items
{
	Inventory::Inventory(std::string name, uint8_t size)
		: m_name(name), m_size(size)
	{

	}

	InventoryItem* Inventory::GetItem(uint8_t slot)
	{
		return m_items[slot];
	}

}
