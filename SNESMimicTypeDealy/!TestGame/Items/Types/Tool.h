#pragma once

#include "../InventoryItem.h"
#include "../../../Objects/MiscState.h"

#define ITEM_PREFIX_TOOL 't'

namespace GAME_NAME::Items
{
	class Tool
		: public InventoryItem
	{
	public:
		Tool() = default;

		Tool(ITEM_TYPE type, int uses);

		SaveParam& Encode() override final;
		void Decode(const SaveParam& params) override final;

		inline const char&& getPrefix() override { return ITEM_PREFIX_TOOL; }
	protected:
		int m_uses SERIALIZED;
	};
}