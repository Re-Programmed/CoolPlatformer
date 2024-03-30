#pragma once

#include "../InventoryItem.h"
#include "../../../Objects/MiscState.h"

namespace GAME_NAME::Items
{
	class Tool
		: public InventoryItem
	{
	public:
		Tool(ITEM_TYPE type, int uses);

		SaveParam Encode() override final;
		void Decode(SaveParam params) override final;

	protected:
		int m_uses SERIALIZED;
	};
}