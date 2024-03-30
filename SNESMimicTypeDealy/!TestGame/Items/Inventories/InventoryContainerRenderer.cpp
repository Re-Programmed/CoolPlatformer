#include "InventoryContainerRenderer.h"

#include "../../../Utils/CollisionDetection.h"

namespace GAME_NAME::Items::Inventories
{
	std::shared_ptr<InventoryContainer> InventoryContainerRenderer::m_currentContainer;
	std::vector<std::shared_ptr<StaticGUIElement>> InventoryContainerRenderer::m_renderedSlots;
	std::vector<std::shared_ptr<StaticGUIElement>> InventoryContainerRenderer::m_renderedSlotItems;

	StaticGUIElement* const InventoryContainerRenderer::m_backgroundCover = new StaticGUIElement(Vec2(0, 0), Vec2(580, 256), 1);

	void InventoryContainerRenderer::OpenInventoryContainer(InventoryContainer* container)
	{
		m_backgroundCover->SetSprite(Renderer::GetSprite(SpriteBase(-1)));
		Renderer::LoadGUIElement(m_backgroundCover);

		if (m_currentContainer != nullptr)
		{
			m_currentContainer->CloseGUI();
		}

		m_currentContainer = std::shared_ptr<InventoryContainer>(m_currentContainer);

		const uint8_t size = container->GetSize();
		for (uint8_t s = 0; s < size; s++)
		{
			Inventory::ReturnItem item = container->GetItem(s);
			//Create slot and add item to the slot.
			createSlot(s, item);
		}
		
		//Prevent the player from moving.
		TestGame::ThePlayer->SetFrozen(true);
	}

	void InventoryContainerRenderer::CloseCurrentContainer()
	{
		Renderer::UnloadGUIElement(m_backgroundCover);

		for (std::shared_ptr<StaticGUIElement> slot : m_renderedSlots)
		{
			Renderer::UnloadGUIElement(slot.get());
		}

		for (std::shared_ptr<StaticGUIElement> slotItem : m_renderedSlotItems)
		{
			Renderer::UnloadGUIElement(slotItem.get());
		}

		m_currentContainer = nullptr;

		//Allow the player to move.
		TestGame::ThePlayer->SetFrozen(false);
	}

	void InventoryContainerRenderer::UpdateCurrentInventoryContainer()
	{
		//Check if the user is clicking on a slot and call the respective clickSlot method.
		if (InputManager::GetMouseButton(0))
		{
			for (uint8_t i = 0; i < m_renderedSlots.size(); i++)
			{
				if (CollisionDetection::PointWithinBoxBL(InputManager::GetMousePosition(), m_renderedSlots[i]->GetPosition(), m_renderedSlots[i]->GetScale()))
				{
					clickSlot(i);
					break;
				}
			}
		}
	}

	void InventoryContainerRenderer::createSlot(uint8_t index, Inventory::ReturnItem item)
	{
		//Position of slot based on defines in header and the current index.
		Vec2 pos(INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_X + (INVENTORY_CONTAINER_RENDERER_SLOT_SPACING * (index % INVENTORY_CONTAINER_RENDERER_ROW_SIZE)), INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_Y + (INVENTORY_CONTAINER_RENDERER_SLOT_SPACING * (index / INVENTORY_CONTAINER_RENDERER_ROW_SIZE)));

		//Create the slot.
		std::shared_ptr<StaticGUIElement> slot(new StaticGUIElement(pos, Vec2(INVENTORY_CONTAINER_RENDERER_SLOT_SCALE), Renderer::GetSprite(INVENTORY_UNSELECTED_SLOT_SPRITE)->GetSpriteId()));
		m_renderedSlots.push_back(slot);
		Renderer::LoadGUIElement(slot.get(), 1);

		if (!item.ri_IsNull)
		{
			GLuint texture = Items::ITEMTYPE_GetItemTypeTexture(item.ri_Item->GetType())->GetSpriteId();
			std::shared_ptr<StaticGUIElement> slotItem(new StaticGUIElement(pos + Vec2(INVENTORY_CONTAINER_RENDERER_ITEM_SCALEDOWN), Vec2(INVENTORY_CONTAINER_RENDERER_SLOT_SCALE - INVENTORY_CONTAINER_RENDERER_ITEM_SCALEDOWN * 2), texture));
			m_renderedSlotItems.push_back(slotItem);
			Renderer::LoadGUIElement(slotItem.get(), 1);
		}
	}

	void InventoryContainerRenderer::clickSlot(uint8_t index)
	{

	}
}
