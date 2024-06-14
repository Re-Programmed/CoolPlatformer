#include "Inventory.h"

namespace GAME_NAME::Items
{
	Inventory::Inventory(std::string name, uint8_t size)
		: m_name(name), m_size(size)
	{

	}

	Inventory::ReturnItem Inventory::GetItem(uint8_t slot)
	{
		if (m_items.size() <= slot) { return { nullptr, true }; }
		if (m_items[slot] == nullptr) { return { nullptr, true }; }

		return { m_items[slot], false };
	}

	int Inventory::AddItem(InventoryItem* item)
	{
		//Search for a null spot, if none is found try to append the item at the end of the array.
		for (uint8_t i = 0; i < m_items.size(); i++)
		{
			if (m_items[i] == nullptr)
			{
				m_items[i] = item;
				return i;
			}
		}
		
		if (m_items.size() >= m_size)
		{
			return -1;
		}
		
		m_items.push_back(item);

		return (int)m_items.size() - 1;
	}

	bool Inventory::SetItem(uint8_t slot, InventoryItem* item)
	{
		//If the slot given is not in within inventory size, fail.
		if (slot >= m_size)
		{
			return false;
		}

		//If the inventory vector is too small to support the new set item, expand it until it fits by adding nullptr references.
		while (m_items.size() < slot)
		{
			m_items.push_back(nullptr);
		}

		//Update the given slot.
		m_items[slot] = item;

		return true;
	}

}
