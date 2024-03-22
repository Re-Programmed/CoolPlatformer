#include "Tool.h"

namespace GAME_NAME::Items
{
	Tool::Tool(ITEM_TYPE type, float uses)
		: InventoryItem(type), m_uses(uses)
	{

	}

	MiscState::SaveParam* Tool::Encode(size_t& paramSize)
	{
		MiscState::SaveParam params[2]{
			InventoryItem::Encode(paramSize)[0],
			SaveParam("Uses", std::to_string(m_uses))
		};

		paramSize = 2;

		return params;
	}

	void Tool::Decode(SaveParam params[])
	{
		InventoryItem::Decode(params);
		
		m_uses = std::stoi(params[1].Value);
	}

}