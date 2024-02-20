#include "InventoryContainer.h"
#include <cstdarg>
#include "../../../Input/InputManager.h"
#include "../../InputDisplay/DisplayIconManager.h"
#include "InventoryContainerRenderer.h"

namespace GAME_NAME::Items::Inventories
{
	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation)
		: Inventory(name, size), Interactable(OPEN_INVENTORY_CONTAINER_KEY, InputManager::KEY_STATE_NONE, position, scale, sprite, rotation)
	{

	}

	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation, int itemCount, ...)
		: Inventory(name, size), Interactable(OPEN_INVENTORY_CONTAINER_KEY, InputManager::KEY_STATE_NONE, position, scale, sprite, rotation)
	{
using namespace std;
		va_list args;
		va_start(args, itemCount);

		for (int i = 0; i < itemCount; i++)
		{
			AddItem(va_arg(args, InventoryItem));
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

	void InventoryContainer::Update(GLFWwindow* window)
	{
		if (m_isOpen)
		{
			if (InputManager::GetKeyUpDown(OPEN_INVENTORY_CONTAINER_KEY) & InputManager::KEY_STATE_PRESSED)
			{
				CloseGUI();
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
