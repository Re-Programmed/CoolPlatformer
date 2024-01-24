#pragma once
#include <cstdint>
#include <string>
#include "InventoryItem.h"

namespace GAME_NAME::Items
{
	class Inventory
	{
	public:
		Inventory(std::string name, uint8_t size);

		InventoryItem* GetItem(uint8_t slot);
	private:
		const std::string m_name;
		uint8_t m_size;

		std::vector<InventoryItem*> m_items;
	};
}