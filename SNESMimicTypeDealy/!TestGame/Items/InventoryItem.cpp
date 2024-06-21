#include "./InventoryItem.h"

#include "./Types/Tool.h"

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



		InventoryItem* InventoryItem::DecodeItemString(std::string data)
		{
			//First char indicates the type of the item, and what class should be used to represent it.
			const char& firstChar = data.at(0);

			InventoryItem* item = new InventoryItem();

			switch (firstChar)
			{
			case ITEM_PREFIX_ITEM:
				//Decode the item.
				item->Decode(data);

				//Item should be null.
				if (item->GetType() == NULL_ITEM)
				{
					delete item;
					item = nullptr;
				}

				break;
			case ITEM_PREFIX_TOOL:
				//Change item to point to a new tool.
				delete item;
				Tool* t = new Tool();
				t->Decode(data);
				item = t;
				break;
			}

			return item;
		}
	}
}