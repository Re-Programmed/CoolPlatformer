#pragma once
#include "../../Rendering/Sprite.h"
#include "../../Rendering/Renderers/Renderer.h"

#include <unordered_map>

#define ITEM_PREFIX_ITEM 'i'
#define ITEM_PREFIX_TOOL 't'
#define ITEM_PREFIX_WEAPON 'w'

namespace GAME_NAME
{
	namespace Items
	{
#define ITEM_COUNT 7
		/// <summary>
		/// An enum for the types of items in the game.
		/// </summary>
		enum ITEM_TYPE
		{
			LOG = 0,
			LEAVES = 1,
			STONE = 2,
			SCRAP_AXE = 3,
			NULL_ITEM = 4, //NULL ITEM IS 4 (used for saving data about items that are not there)
			WOODEN_SHOES = 5,
			SHARP_STICK = 6
		};

		/// <summary>
		/// Different actions that tools can perform. Can be checked for when determining wether the player can perform some action based on what tool they are holding.
		/// </summary>
		enum TOOL_ACTION
		{
			CHOP = 0b00001, //Can cut down trees.
			EQUIPMENT = 0b00010, //Can be equipped to equipment slots.
			MINE = 0b00100, //Can break BreakableBlocks. (provide a strength attribute)
			WEAPON = 0b01000 //Can be used to attack. (provide a damage, power consumption, reload attribute, and area of effect [damage,powerconsume,reloadseconds,AOE(integer)])
		};

		/// <summary>
		/// ItemData is the data for different item types that remains constant.
		/// (ex. Every log will always be named "Log," so the name is stored in the data for log.
		/// </summary>
		struct ItemData
		{
			/// <summary>
			/// The name of the item.
			/// </summary>
			const std::string DisplayName;
			/// <summary>
			/// The texture for the inventory display of the item.
			/// </summary>
			const int16_t Texture; //WHY was this uint :(:(:( this caused so umuch pain.
			/// <summary>
			/// The texture for holding the item. 
			/// </summary>
			const int16_t HeldTexture;
			/// <summary>
			/// A flag list of things the item can do.
			/// </summary>
			const uint16_t Actions = 0;
			/// <summary>
			/// Stores data about the items actions like its strength.
			/// </summary>
			const std::unordered_map<TOOL_ACTION, std::string> Attributes;
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
			{ "(Temp) Axe", 56, SpriteBase(65), CHOP & WEAPON, { { TOOL_ACTION::CHOP , "1" }, { TOOL_ACTION::WEAPON, "10,0,0.9,15" }}},
			{ "Unknown", 0, NO_HELD_TEXTURE },
			{ "Wooden Shoes", 18, NO_HELD_TEXTURE, EQUIPMENT, { { TOOL_ACTION::EQUIPMENT, "Health:10" } } },
			{ "Sharp Stick", SpriteBase(118), SpriteBase(118), WEAPON, {{TOOL_ACTION::WEAPON, "3,0,0.2,24"}}}
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