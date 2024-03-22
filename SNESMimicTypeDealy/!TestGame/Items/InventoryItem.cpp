#include "./InventoryItem.h"

namespace GAME_NAME
{
	namespace Items
	{
		InventoryItem::InventoryItem(ITEM_TYPE type)
			: m_itemType(type)
		{

		}

		MiscState::SaveParam* InventoryItem::Encode(size_t& paramSize)
		{
			SaveParam params[1]{
				SaveParam("type", std::to_string(m_itemType))
			};

			paramSize = 1;

			return params;
		}

		void InventoryItem::Decode(MiscState::SaveParam params[])
		{
			m_itemType = (Items::ITEM_TYPE)std::stoi(params[0].Value);
		}
	}
}