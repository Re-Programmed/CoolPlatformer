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
		
		/// <summary>
		/// Returns a pointer to the item in the given slot.
		/// </summary>
		/// <param name="slot">The slot of the inventory to access the item from.</param>
		std::unique_ptr<InventoryItem> GetItem(uint8_t slot);

		/// <summary>
		/// Adds an item to the inventory at the last slot.
		/// </summary>
		/// <param name="item">The item to add.</param>
		/// <returns>The slot the item was added to. (-1 if the inventory is full)</returns>
		int AddItem(InventoryItem item);
	protected:
		/// <summary>
		/// The name of the inventory, useful for rendering a graphical display of the inventory.
		/// </summary>
		const std::string m_name;
		/// <summary>
		/// The maximum size of the inventory.
		/// </summary>
		uint8_t m_size;

		std::vector<InventoryItem> m_items;
	};
}