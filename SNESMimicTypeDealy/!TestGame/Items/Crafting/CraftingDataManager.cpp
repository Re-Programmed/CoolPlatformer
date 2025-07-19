#include "CraftingDataManager.h"

namespace GAME_NAME::Items::Crafting
{
	std::array<const Recipe, CRAFTING_DATA_NUM_RECIPES> CraftingDataManager::m_recipes = {
		Recipe{ SCRAP_AXE, NULL_ITEM, NULL_ITEM, LOG },
		Recipe{ LEAVES, LEAVES, NULL_ITEM, SCRAP_AXE },
		Recipe{ SHARP_STICK, SHARP_STICK, SHARP_STICK, WOODEN_SHOES },
		Recipe{ LOG, NULL_ITEM, NULL_ITEM, LOG }
	};
}
