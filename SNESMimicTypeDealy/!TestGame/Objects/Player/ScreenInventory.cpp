#include "ScreenInventory.h"
#include "../../../Input/InputManager.h"
#include "../../TestGame.h"

#include "../../Items/Types/Tool.h"

#include "../../../CustomCompileOptions.h"

#define INVENTORY_SLOT_PADDING 5.f

namespace GAME_NAME
{

	ScreenInventory::ScreenInventory()
		: Inventory("Screen Inventory", 3), MiscStateGroup("si")
	{
		m_slots[0] = new GUI::StaticGUIElement(Vec2(4, 20), Vec2(16, 16), Renderer::GetSprite(INVENTORY_SELECTED_SLOT_SPRITE)->GetSpriteId());
		m_slots[1] = new GUI::StaticGUIElement(Vec2(24, 20), Vec2(16, 16), Renderer::GetSprite(INVENTORY_UNSELECTED_SLOT_SPRITE)->GetSpriteId());
		m_slots[2] = new GUI::StaticGUIElement(Vec2(44, 20), Vec2(16, 16), Renderer::GetSprite(INVENTORY_UNSELECTED_SLOT_SPRITE)->GetSpriteId());

		Renderer::LoadGUIElement(m_slots[0]);
		Renderer::LoadGUIElement(m_slots[1]);
		Renderer::LoadGUIElement(m_slots[2]);

		std::shared_ptr<std::vector<std::string>> data = getStates();

using namespace Items;

		for (int i = 0; i < data->size(); i++)
		{
			//First char indicates the type of the item, and what class should be used to represent it.
			const char& firstChar = data->at(i).at(0);

			InventoryItem* item = new InventoryItem();

			switch (firstChar)
			{
			case ITEM_PREFIX_ITEM:
				//Decode the item.
				item->Decode(data->at(i));
				break;
			case ITEM_PREFIX_TOOL:
				//Change item to point to a new tool.
				delete item;
				Tool* t = new Tool();
				t->Decode(data->at(i));
				item = t;
				break;
			}

			AddItem(item);
		}
	}

	void ScreenInventory::Update()
	{
		{
			if (InputManager::GetKeyUpDown(PLAYER_SCREEN_INVENTORY_SLOT_1) & InputManager::KEY_STATE_PRESSED)
			{
				selectSlot(1);
			}

			if (InputManager::GetKeyUpDown(PLAYER_SCREEN_INVENTORY_SLOT_2) & InputManager::KEY_STATE_PRESSED)
			{
				selectSlot(2);
			}

			if (InputManager::GetKeyUpDown(PLAYER_SCREEN_INVENTORY_SLOT_3) & InputManager::KEY_STATE_PRESSED)
			{
				selectSlot(3);
			}
		}
	}

	int ScreenInventory::AddItem(Items::InventoryItem* item)
	{
		int s = Inventory::AddItem(item);

		if (s == -1)
		{
			return -1;
		}

		Sprite* sprite = Items::ITEMTYPE_GetItemTypeTexture(item->GetType());
		GUI::StaticGUIElement* itemDisplay = new GUI::StaticGUIElement(m_slots[s]->GetPosition() + (INVENTORY_SLOT_PADDING/2.f), m_slots[s]->GetScale() - Vec2(INVENTORY_SLOT_PADDING), sprite->GetSpriteId());
		delete sprite;
		Renderer::LoadGUIElement(itemDisplay, 1);

		//Remove all save data.
		clearStates();
		//Add save data for all items.
		for (Items::InventoryItem* item : m_items)
		{
			assignState(item);
		}
		
		return s;
	}


	void ScreenInventory::selectSlot(InventorySlot slot)
	{
		slot--;
		for (InventorySlot i = 0; i < 3; i++)
		{
			if (slot == i)
			{
				m_slots[i]->SetSprite(Renderer::GetSprite(INVENTORY_SELECTED_SLOT_SPRITE));

				if (m_items.size() > i)
				{
					TestGame::ThePlayer->SetHeldItem(m_items[i]);
				}
				else {
					TestGame::ThePlayer->RemoveHeldItem();
				}

				continue;
			}

			m_slots[i]->SetSprite(Renderer::GetSprite(INVENTORY_UNSELECTED_SLOT_SPRITE));
		}
	}
}
