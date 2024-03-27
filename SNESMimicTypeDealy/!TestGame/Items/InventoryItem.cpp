#include "./InventoryItem.h"

namespace GAME_NAME
{
	namespace Items
	{
		InventoryItem::InventoryItem(ITEM_TYPE type)
			: m_itemType(type)
		{

		}

		InventoryItem::InventoryItem()
		{

		}

		MiscState::SaveParam InventoryItem::Encode()
		{
			return std::to_string(m_itemType);
		}

		//Expects a string that is purely a number representing the type.
		void InventoryItem::Decode(MiscState::SaveParam param)
		{
			m_itemType = (Items::ITEM_TYPE)std::stoi(param);
		}
	}
}