#include "Inventory.h"

namespace GAME_NAME::Items
{
	Inventory::Inventory(std::string name, uint8_t size)
		: m_name(name), m_size(size)
	{

	}

	std::unique_ptr<InventoryItem> Inventory::GetItem(uint8_t slot)
	{
		return std::unique_ptr<InventoryItem>(&m_items[slot]);
	}

	int Inventory::AddItem(InventoryItem item)
	{
		if (m_items.size() >= m_size)
		{
			return -1;
		}
		
		m_items.push_back(item);

		return (int)m_items.size() - 1;
	}

}
