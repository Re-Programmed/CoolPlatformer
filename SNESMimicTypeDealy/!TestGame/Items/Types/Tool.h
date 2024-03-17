#pragma once

#include "../InventoryItem.h"
#include "../../../Objects/MiscState.h"

namespace GAME_NAME::Items
{
	class Tool
		: public InventoryItem, public MiscState<Tool>
	{
	public:
		Tool(ITEM_TYPE type, float uses);

		Tool Decode(SaveParam params[]) override;
		SaveParam* Encode(Tool tool) override;

	protected:
		float m_uses;
	};
}