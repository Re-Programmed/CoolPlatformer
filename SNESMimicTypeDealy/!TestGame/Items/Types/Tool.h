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

		SaveParam* Encode(size_t& paramSize) override;
		void Decode(SaveParam params[]) override;

	protected:
		float m_uses;
	};
}