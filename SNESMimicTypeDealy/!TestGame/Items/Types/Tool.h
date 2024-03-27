#pragma once

#include "../InventoryItem.h"
#include "../../../Objects/MiscState.h"

namespace GAME_NAME::Items
{
	class Tool
		: public InventoryItem
	{
	public:
		Tool(ITEM_TYPE type, float uses);

		SaveParam Encode() override final;
		void Decode(SaveParam params) override final;

	protected:
		float m_uses SERIALIZED;
	};
}