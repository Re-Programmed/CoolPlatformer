#include "Inventory.h"

namespace GAME_NAME::Items
{
	Inventory::Inventory(std::string name, uint8_t size)
		: m_name(name), m_size(size)
	{

	}

	Inventory::ReturnItem Inventory::GetItem(uint8_t slot)
	{
		if (m_items.size() <= slot) { return { m_items[0], true }; }

		return { m_items[slot], false };
	}

	int Inventory::AddItem(InventoryItem* item)
	{
		if (m_items.size() >= m_size)
		{
			return -1;
		}
		
		m_items.push_back(item);

		return (int)m_items.size() - 1;
	}

}
