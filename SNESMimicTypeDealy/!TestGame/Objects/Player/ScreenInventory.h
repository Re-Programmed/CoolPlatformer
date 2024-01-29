#pragma once
#include "../../Items/Inventory.h"
#include "../../../Objects/GUI/StaticGUIElement.h"
#include "../../Items/InventoryItem.h"

namespace GAME_NAME
{
	typedef uint8_t InventorySlot;
	class ScreenInventory
		: public GAME_NAME::Items::Inventory
	{
	public:
		ScreenInventory();

		void Update();

		int AddItem(Items::InventoryItem* item);
	private:
		GUI::StaticGUIElement* m_slots[3];

		void selectSlot(InventorySlot slot);
	};
}