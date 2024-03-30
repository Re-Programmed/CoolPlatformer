#pragma once
#include "../../Rendering/Sprite.h"
#include "../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME
{
	namespace Items
	{
#define ITEM_COUNT 4
		//An enum for the types of items in the game.
		enum ITEM_TYPE
		{
			LOG = 0,
			LEAVES = 1,
			STONE,	
			SCRAP_AXE
		};

		//An array containing the sprite for each of the items in order of the ITEM_TYPE enum.
		const int ITEM_TEXTURES[ITEM_COUNT]{
			18,	//LOG
			18,	//LEAVES
			55,	//STONE (add to have randomized textures)
			56	//SCRAP_AXE
		};

		const std::string ITEM_DISPLAY_NAME[ITEM_COUNT]{
			"Log",
			"Leaves",
			"Stone",
			"Axe"
		};


		/// <summary>
		/// Returns the corresponding texture for the given item type.
		/// </summary>
		/// <param name="itemType">The type of item to get the texture of.</param>
		/// <returns>The texture relating to the given item type.</returns>
		inline Rendering::Sprite* const ITEMTYPE_GetItemTypeTexture(ITEM_TYPE itemType)
		{
			return Renderer::GetSprite(ITEM_TEXTURES[itemType]);
		}

		inline const std::string ITEMTYPE_GetItemTypeName(ITEM_TYPE itemType)
		{
			return ITEM_DISPLAY_NAME[itemType];
		}
	}
}