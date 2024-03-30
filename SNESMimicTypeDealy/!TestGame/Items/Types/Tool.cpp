#include "Tool.h"

namespace GAME_NAME::Items
{
	Tool::Tool(ITEM_TYPE type, int uses)
		: InventoryItem(type), m_uses(uses)
	{

	}

	MiscState::SaveParam Tool::Encode()
	{
		MiscState::SaveParam param = InventoryItem::Encode();

		param += std::string("+").append(std::to_string(m_uses));

		return param;
	}

	void Tool::Decode(SaveParam params)
	{
		std::string usesEncoded = params;
		usesEncoded.erase(usesEncoded.begin(), usesEncoded.end() - usesEncoded.find('+'));
		m_uses = std::stoi(usesEncoded);

		std::string type = params;
		type.erase(type.begin() + type.find('+'), type.end());

		InventoryItem::Decode(type);
	}

}