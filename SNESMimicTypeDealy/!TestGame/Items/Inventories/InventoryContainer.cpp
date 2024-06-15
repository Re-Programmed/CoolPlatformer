#include "InventoryContainer.h"
#include <cstdarg>
#include "../../../Input/InputManager.h"
#include "../../InputDisplay/DisplayIconManager.h"
#include "InventoryContainerRenderer.h"
#include "../../../Resources/Save/SaveManager.h"
#include "../../../Objects/StateSaver.h"
#include "../Types/Tool.h"

namespace GAME_NAME::Items::Inventories
{
	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, float rotation)
		: Inventory(name, size), Interactable(OPEN_INVENTORY_CONTAINER_KEY, InputManager::KEY_STATE_NONE, position, scale, sprite, rotation), GameObjectState(saveID)
	{
		LoadState();
	}

	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, float rotation, int itemCount, ...)
		: Inventory(name, size), Interactable(OPEN_INVENTORY_CONTAINER_KEY, InputManager::KEY_STATE_NONE, position, scale, sprite, rotation), GameObjectState(saveID)
	{
		LoadState();

using namespace std;
		va_list args;
		va_start(args, itemCount);

		for (int i = 0; i < itemCount; i++)
		{
			AddItem(va_arg(args, InventoryItem*));
		}

		va_end(args);
	}

	void InventoryContainer::OpenGUI()
	{
		if (m_isOpen) { return; }

		InventoryContainerRenderer::OpenInventoryContainer(this);
		m_isOpen = true;
	}

	void InventoryContainer::CloseGUI()
	{
		if (!m_isOpen) { return; }

		InventoryContainerRenderer::CloseCurrentContainer();
		m_isOpen = false;
	}

	void InventoryContainer::LoadState()
	{
		std::string loadData("");
		Resources::SaveManager::GetLevelString(loadData, m_objectSaveID);

		if (loadData.size() < 3) { return; }

		m_loadedFromState = true;

		std::stringstream ss(loadData);
		std::string line;

		int i = 0;
		while (std::getline(ss, line, '/'))
		{
			if (line.size() < 1) { continue; }
			if (line == "NULL")
			{
				SetItem(i, nullptr);
				i++;
				continue;
			}
			
			//Found an item in saved data, decode it.
			const char& firstChar = line.at(0);

			InventoryItem* item = new InventoryItem();

			switch (firstChar)
			{
			case ITEM_PREFIX_ITEM:
				//Decode the item.
				item->Decode(line);

				//Item should be null.
				if (item->GetType() == NULL_ITEM)
				{
					delete item;
					item = nullptr;
				}

				break;
			case ITEM_PREFIX_TOOL:
				//Change item to point to a new tool.
				delete item;
				Tool* t = new Tool();
				t->Decode(line);
				item = t;
				break;
			}

			SetItem(i, item);
			i++;
		}
	}

	void InventoryContainer::SaveState()
	{
		std::string data("");

		for (int i = 0; i < m_size; i++)
		{
			ReturnItem item = GetItem(i);
			if (!item.ri_IsNull)
			{
				data += item.ri_Item->Encode();
			}
			else {
				data += "NULL";
			}

			data += "/";
		}

		Resources::SaveManager::SaveLevelString(data, m_objectSaveID);
	}

	void InventoryContainer::Update(GLFWwindow* window)
	{
		if (m_isOpen)
		{
			if (InputManager::GetKeyUpDown(OPEN_INVENTORY_CONTAINER_KEY) & InputManager::KEY_STATE_PRESSED)
			{
				CloseGUI();
			}
			
			//If the inventory is open, update it to detect clicking on slots.
			InventoryContainerRenderer::UpdateCurrentInventoryContainer();

			//The inventory is open so changes may have been made, set to be saved.
			if (!m_toBeSaved)
			{
				StateSaver::RegisterToBeSaved(this);
				SetToBeSaved(true);
			}
		}

		Interactable::Update(window);
	}

	void InventoryContainer::onInteract(std::shared_ptr<GAME_NAME::Objects::Player::Player> player, InputManager::KEY_STATE state)
	{
		if (m_isOpen)
		{
			return;
		}

using namespace GAME_NAME;
		Input::DisplayIconManager::ShowKeyInputDisplay(Input::DisplayIconManager::INPUT_DISPLAY_KEY_E, TestGame::ThePlayer->GetPosition() + Vec2(TestGame::ThePlayer->GetScale() + Vec2(3, -5)));

		if (state & InputManager::KEY_STATE_PRESSED)
		{
			OpenGUI();
		}
	}

}
