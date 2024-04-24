#pragma once
#include "../../Items/Inventory.h"
#include "../../../Objects/GUI/StaticGUIElement.h"
#include "../../Items/InventoryItem.h"
#include "../../../Objects/MiscStateGroup.h"

namespace GAME_NAME
{
	typedef uint8_t InventorySlot;
	class ScreenInventory
		: public GAME_NAME::Items::Inventory, public MiscStateGroup
	{
	public:
		ScreenInventory();

		void Update();

		int AddItem(Items::InventoryItem* item, bool ignoreSave = false);

		inline Items::InventoryItem* const GetHeldItem()
		{
			if (m_items.size() <= m_saveMetadata.SelectedSlot)
			{
				return nullptr;
			}

			return m_items[m_saveMetadata.SelectedSlot - 1];
		}
	private:
		///Used to store the save data for the ScreenInventory such as the currently selected item.
		struct ScreenInventoryMetadata
			: public MiscState
		{
			InventorySlot SelectedSlot = 0;

			MiscState::SaveParam Encode() final override
			{
				return std::to_string(SelectedSlot);
			}

			void Decode(const MiscState::SaveParam params) final override
			{
				SelectedSlot = std::stoi(params);
			}
		};
		ScreenInventoryMetadata m_saveMetadata;

		GUI::StaticGUIElement* m_slots[3];

		void selectSlot(InventorySlot slot, bool updatePlayerDisplay = true);

		void updateSave();
	};
}