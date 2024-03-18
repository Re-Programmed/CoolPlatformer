#pragma once
#include "./InventoryContainer.h"
#include "../../../CustomCompileOptions.h"

#define INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_X 20	//X position of the first slot rendered in an inventory.
#define INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_Y 128	//Y position of the first slot rendered in an inventory.

#define INVENTORY_CONTAINER_RENDERER_SLOT_SCALE 24			//Scale of slots renderered in an inventory.
#define INVENTORY_CONTAINER_RENDERER_SLOT_SPACING 32		//Distance between slots rendered in an inventory.

#define INVENTORY_CONTAINER_RENDERER_ROW_SIZE 9				//Number of slots in one row of a rendered inventory.

#define INVENTORY_CONTAINER_RENDERER_ITEM_SCALEDOWN 4		//How much to shrink items displayed in slots.

namespace GAME_NAME::Items::Inventories
{
	class InventoryContainerRenderer
	{
	public:
		static void OpenInventoryContainer(InventoryContainer* container);
		static void CloseCurrentContainer();

		/// <summary>
		/// Should be called every frame as long as there is an inventory container currently open.
		/// </summary>
		static void UpdateCurrentInventoryContainer();
	private:
		static std::shared_ptr<InventoryContainer> m_currentContainer;
		static std::vector<std::shared_ptr<StaticGUIElement>> m_renderedSlots;
		static std::vector<std::shared_ptr<StaticGUIElement>> m_renderedSlotItems;

		static StaticGUIElement* const m_backgroundCover;

		/// <summary>
		/// Create a slot for the current inventory.
		/// </summary>
		/// <param name="index">Slot Index / Number.</param>
		static void createSlot(uint8_t index, Inventory::ReturnItem item);
		
		static void clickSlot(uint8_t index);
	};
}