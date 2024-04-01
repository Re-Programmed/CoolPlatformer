#include "./InventoryItem.h"

namespace GAME_NAME
{
	namespace Items
	{
		InventoryItem::InventoryItem(ITEM_TYPE type)
			: m_itemType(type)
		{

		}

		InventoryItem::InventoryItem(const InventoryItem& item)
			: m_itemType(item.m_itemType)
		{
			
		}

		InventoryItem::InventoryItem(InventoryItem&& item) noexcept
		{
			m_itemType = item.m_itemType;
		}


		MiscState::SaveParam InventoryItem::Encode()
		{
			MiscState::SaveParam param;
			param += getPrefix();
			return param.append(std::to_string(m_itemType));
		}

		//Expects a string that is purely a number representing the type.
		void InventoryItem::Decode(const MiscState::SaveParam param)
		{
			//Get the item type, ignore the first character that denotes item type.
			m_itemType = (Items::ITEM_TYPE)std::stoi(param.substr(1));
		}
	}
}