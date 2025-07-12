#pragma once
#include "../../../Objects/GUI/StaticGUIElement.h"
#include "../ItemType.h"

namespace GAME_NAME::Items::Crafting
{
#define RECIPE_ELEMENT_COUNT 4

using namespace GUI;

	class CraftingMenuManager
	{
	public:
		static void OpenCraftingMenu();

	private:
		static StaticGUIElement* const m_backgroundCover;
		static std::array<std::array<IGUIElement*, RECIPE_ELEMENT_COUNT>, 4> m_recipeDisplays;

		static void addRecipeOption(ITEM_TYPE inputItem);
	};
}