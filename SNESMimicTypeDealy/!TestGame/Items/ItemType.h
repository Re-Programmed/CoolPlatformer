#pragma once
#include "../../Rendering/Sprite.h"
#include "../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME
{
	namespace Items
	{
#define ITEM_COUNT 5
		/// <summary>
		/// An enum for the types of items in the game.
		/// </summary>
		enum ITEM_TYPE
		{
			LOG = 0,
			LEAVES = 1,
			STONE = 2,
			SCRAP_AXE = 3,
			NULL_ITEM = 4 //NULL ITEM IS 4 (used for saving data about items that are not there)
		};

		/// <summary>
		/// Different actions that tools can perform. Can be checked for when determining wether the player can perform some action based on what tool they are holding.
		/// </summary>
		enum TOOL_ACTION
		{
			CHOP = 0b00001 //Can cut down trees.
		};

		/// <summary>
		/// ItemData is the data for different item types that remains constant.
		/// (ex. Every log will always be named "Log," so the name is stored in the data for log.
		/// </summary>
		struct ItemData
		{
			const std::string DisplayName;
			const uint16_t Texture;
			const int16_t HeldTexture;
			const uint16_t Actions = 0;
		};

#define NO_HELD_TEXTURE GLOBAL_SPRITE_BASE

		/// <summary>
		/// A list of the item data for each item type.
		/// </summary>
		const ItemData ITEM_DATA[ITEM_COUNT]
		{
			{ "Log", 18, NO_HELD_TEXTURE },
			{ "Leaves", 18, NO_HELD_TEXTURE },
			{ "Stone", 55, NO_HELD_TEXTURE },
			{ "Axe", 56, SpriteBase(65), CHOP },
			{ "Unknown", 0, NO_HELD_TEXTURE }
		};


		/// <summary>
		/// Returns the corresponding texture for the given item type.
		/// </summary>
		/// <param name="itemType">The type of item to get the texture of.</param>
		/// <returns>The texture relating to the given item type.</returns>
		inline Rendering::Sprite* const ITEMTYPE_GetItemTypeTexture(ITEM_TYPE itemType)
		{
			return Renderer::GetSprite(ITEM_DATA[itemType].Texture);
		}

		/// <summary>
		/// Returns the corresponding name for the given item type. 
		/// </summary>
		/// <param name="itemType">The type of item to get the name of.</param>
		/// <returns>The display name relating to the given item type.</returns>
		inline const std::string ITEMTYPE_GetItemTypeName(ITEM_TYPE itemType)
		{
			return ITEM_DATA[itemType].DisplayName;
		}

		/// <summary>
		/// Returns a const reference to the data of the given item type.
		/// </summary>
		/// <param name="itemType">The type of item to get the data of.</param>
		/// <returns>A const reference to the data relating to the given item type.</returns>
		inline const ItemData& ITEMTYPE_GetItemData(ITEM_TYPE itemType)
		{
			return ITEM_DATA[itemType];
		}
	}
}