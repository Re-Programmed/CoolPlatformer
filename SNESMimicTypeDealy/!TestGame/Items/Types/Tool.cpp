#include "Tool.h"

namespace GAME_NAME::Items
{
	Tool::Tool(ITEM_TYPE type, int uses)
		: InventoryItem(type), m_uses(uses)
	{

	}

	MiscState::SaveParam& Tool::Encode()
	{
		MiscState::SaveParam param = InventoryItem::Encode();

		param += std::string("+").append(std::to_string(m_uses));

		//t_(type)+(uses)
		return param;
	}

	void Tool::Decode(const SaveParam& params)
	{
		m_uses = std::stoi(params.substr(params.find('+') + 1));

		InventoryItem::Decode(params.substr(1, params.find('+')));
	}

}