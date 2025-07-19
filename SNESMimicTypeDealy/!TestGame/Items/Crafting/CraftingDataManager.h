#pragma once

#include "../../Items/ItemType.h"

namespace GAME_NAME::Items::Crafting
{
#define CRAFTING_DATA_NUM_RECIPES 4

	struct Recipe
	{
		ITEM_TYPE Input1, Input2, Input3;
		ITEM_TYPE Return;
	};

	class CraftingDataManager
	{
	public:
		inline static const Recipe& GetRecipe(const int& index)
		{
			return m_recipes[index];
		}
	private:
		static std::array<const Recipe, CRAFTING_DATA_NUM_RECIPES> m_recipes;
	};
}