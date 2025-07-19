#pragma once
#include "../../../Objects/GUI/StaticGUIElement.h"
#include "../ItemType.h"

#include "./CraftingDataManager.h"

namespace GAME_NAME::Items::Crafting
{
#define CRAFTING_MENU_MANAGER_RECIPE_ELEMENT_COUNT 4

using namespace GUI;

	class CraftingMenuManager
	{
	public:
		static void OpenCraftingMenu();

	private:
		static StaticGUIElement* const m_backgroundCover;
		static std::array<std::array<IGUIElement*, CRAFTING_MENU_MANAGER_RECIPE_ELEMENT_COUNT>, CRAFTING_DATA_NUM_RECIPES> m_recipeDisplays;

		static std::array<IGUIElement*, CRAFTING_MENU_MANAGER_RECIPE_ELEMENT_COUNT> addRecipeOption(const ITEM_TYPE& inputItem, const ITEM_TYPE& inputItem2, const ITEM_TYPE& inputItem3, const ITEM_TYPE& returnItem, const int& index);

		static void recipeOptionButtonCallback(int buttonId);
	};
}