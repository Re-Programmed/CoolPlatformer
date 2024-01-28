#pragma once
#include "../../Rendering/Sprite.h"
#include "../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME
{
	namespace Items
	{
		//An enum for the types of items in the game.
		enum ITEM_TYPE
		{
			LOG,
			LEAVES
		};

		//An array containing the sprite for each of the items in order of the ITEM_TYPE enum.
		const unsigned int ITEM_TEXTURES[2]{
			18,
			18
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
	}
}