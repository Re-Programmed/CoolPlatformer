#pragma once
#include "./Items/InventoryItem.h"

/*
	Item inputs:
		Basic Item:
			(i_type)
		Tool:
			(t_type;uses)
*/

namespace GAME_NAME
{
	using namespace Items;
	class ItemMapping
	{
	public:
		static InventoryItem* DeSerialize(std::string itemString);		
	};
}

/*
	ITEM MAPPINGS WILL BE TO CONVERT STRINGS IN LEVEL FILES TO ITEMS THAT CAN BE INSIDE InventoryContainers or FloorItems
	ex.
	(t,1,23)
	^ Would mean a tool with type one and 23 durability.
	(i,2)
	^ Would mean a basic item with type two.
*/