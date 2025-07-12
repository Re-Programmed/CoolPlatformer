#include "CraftingMenuManager.h"

#include "../../../Objects/GUI/GUIButton.h"


namespace GAME_NAME::Items::Crafting
{

	StaticGUIElement* const CraftingMenuManager::m_backgroundCover = new StaticGUIElement(Vec2(0, 0), Vec2(580, 256), 1);

	std::array<std::array<IGUIElement*, RECIPE_ELEMENT_COUNT>, 4>  CraftingMenuManager::m_recipeDisplays;

	void CraftingMenuManager::OpenCraftingMenu()
	{
		Renderer::LoadGUIElement(m_backgroundCover);

		addRecipeOption(LOG);
	}

	void CraftingMenuManager::addRecipeOption(ITEM_TYPE inputItem)
	{
		GUIButton* backing = new GUIButton(Vec2(10, 246 - 30), Vec2(580/3, 30), 1, nullptr);

		Sprite* sp = ITEMTYPE_GetItemTypeTexture(inputItem);
		StaticGUIElement* input_item = new StaticGUIElement(backing->GetPosition() + Vec2{ 4, 15 - 8 }, Vec2{ 16, 16 }, sp->GetSpriteId());
		delete sp;

		Renderer::LoadGUIElement(backing, 2);
		Renderer::LoadGUIElement(input_item, 2);
	}
}