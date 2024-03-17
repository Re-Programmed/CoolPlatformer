#pragma once
#include "./ItemType.h"

namespace GAME_NAME
{
	namespace Items
	{
		/// <summary>
		/// An inventory item represents an item's data.
		/// </summary>
		class InventoryItem
		{
		public:
			/// <summary>
			/// Create an inventory item with type.
			/// </summary>
			/// <param name="type">The type of item to create.</param>
			InventoryItem(ITEM_TYPE type);

			/// <summary>
			/// Returns the type of item.
			/// </summary>
			/// <returns></returns>
			inline ITEM_TYPE GetType()
			{
				return m_itemType;
			}

		protected:
			/// <summary>
			/// The type of the item represented by this InventoryItem.
			/// </summary>
			const ITEM_TYPE m_itemType;
		};
	}
}