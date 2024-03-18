#include "Tool.h"

namespace GAME_NAME::Items
{
	Tool::Tool(ITEM_TYPE type, float uses)
		: InventoryItem(type), m_uses(uses)
	{

	}
	Tool Tool::Decode(SaveParam params[])
	{
		return Tool();
	}

	SaveParam* Tool::Encode(Tool tool)
	{
		return nullptr;
	}
}