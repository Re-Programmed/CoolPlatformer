#include "InventoryContainerRenderer.h"

#include "../../../Utils/CollisionDetection.h"

#define TOOLTIP_HEIGHT 25.6f
#define TOOLTIP_ANIMATION_SPEED 0.06f

namespace GAME_NAME::Items::Inventories
{
	bool InventoryContainerRenderer::m_hidingTooltip = false;

	InventoryContainer* InventoryContainerRenderer::m_currentContainer;
	std::vector<std::shared_ptr<StaticGUIElement>> InventoryContainerRenderer::m_renderedSlots;
	std::vector<std::shared_ptr<StaticGUIElement>> InventoryContainerRenderer::m_renderedSlotItems;

	StaticGUIElement* InventoryContainerRenderer::m_tooltip;

	StaticGUIElement* const InventoryContainerRenderer::m_backgroundCover = new StaticGUIElement(Vec2(0, 0), Vec2(580, 256), 1);

	void InventoryContainerRenderer::OpenInventoryContainer(InventoryContainer* container)
	{
		m_backgroundCover->SetSprite(Renderer::GetSprite(SpriteBase(-1)));
		Renderer::LoadGUIElement(m_backgroundCover);
		
		m_tooltip = new StaticGUIElement({ 0, 0 }, { 43, 25 }, Renderer::GetSprite(SpriteBase(73))->GetSpriteId());

		Renderer::LoadGUIElement(m_tooltip, 2);

		if (m_currentContainer != nullptr)
		{
			HideRenderPlayerSlots();
			m_currentContainer->CloseGUI();
		}

		//Update current container.
		m_currentContainer = container;

		const uint8_t size = container->GetSize();
		for (uint8_t s = 0; s < size; s++)
		{
			Inventory::ReturnItem item = container->GetItem(s);
			//Create slot and add item to the slot.
			createSlot(s, item);
		}
		
		//Prevent the player from moving.
		TestGame::ThePlayer->SetFrozen(true);

		BeginRenderPlayerSlots();
	}

	void InventoryContainerRenderer::CloseCurrentContainer()
	{
		Renderer::UnloadGUIElement(m_backgroundCover);

		Renderer::UnloadGUIElement(m_tooltip, 2);

		//delete m_tooltip;

		for (std::shared_ptr<StaticGUIElement> slot : m_renderedSlots)
		{
			Renderer::UnloadGUIElement(slot.get());
		}

		for (std::shared_ptr<StaticGUIElement> slotItem : m_renderedSlotItems)
		{
			Renderer::UnloadGUIElement(slotItem.get());
		}

		m_renderedSlotItems.clear();

		m_currentContainer = nullptr;

		//Allow the player to move.
		TestGame::ThePlayer->SetFrozen(false);

		HideRenderPlayerSlots();
	}

	void InventoryContainerRenderer::BeginRenderPlayerSlots()
	{
		//Hide main screen player slots.
		TestGame::ThePlayer->GetInventory()->HidePlayerSlots();

		uint8_t size = TestGame::ThePlayer->GetInventory()->GetSize();

		//Attempt to center the player inventory display.
		float calculatedStartOffset =  (((float)(INVENTORY_CONTAINER_RENDERER_ROW_SIZE - size) / 2.f - 0.7f) * (INVENTORY_CONTAINER_RENDERER_SLOT_SCALE + INVENTORY_CONTAINER_RENDERER_SLOT_SPACING/2));

		for (int i = 0; i < size; i++)
		{
			Inventory::ReturnItem ret = TestGame::ThePlayer->GetInventory()->GetItem(i);

			createSlot((m_currentContainer->GetSize() + (m_currentContainer->GetSize() % INVENTORY_CONTAINER_RENDERER_ROW_SIZE)) + i, ret, calculatedStartOffset);
		}
	}

	void InventoryContainerRenderer::HideRenderPlayerSlots()
	{
		TestGame::ThePlayer->GetInventory()->ShowPlayerSlots();
	}

	void InventoryContainerRenderer::UpdateCurrentInventoryContainer()
	{
		for (uint8_t i = 0; i < m_renderedSlots.size(); i++)
		{
			if (CollisionDetection::PointWithinBoxBL(InputManager::GetMouseScreenPosition(), m_renderedSlots[i]->GetPosition(), m_renderedSlots[i]->GetScale()))
			{
				//Check if the user is clicking on a slot and call the respective clickSlot method.
				if (InputManager::GetMouseButton(0))
				{
					clickSlot(i);
				}

				updateTooltip(i);

				//Return since only one slot will ever be hovered.
				return;
			}
		}
		
		updateTooltip(0, true);
	}

	void InventoryContainerRenderer::createSlot(uint8_t index, Inventory::ReturnItem item, float addXOffset)
	{
		//Position of slot based on defines in header and the current index.
		Vec2 pos(INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_X + addXOffset + (INVENTORY_CONTAINER_RENDERER_SLOT_SPACING * (index % INVENTORY_CONTAINER_RENDERER_ROW_SIZE)), INVENTORY_CONTAINER_RENDERER_SLOT_START_POS_Y - (INVENTORY_CONTAINER_RENDERER_SLOT_SPACING * (index / INVENTORY_CONTAINER_RENDERER_ROW_SIZE)));

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

			std::cout << "LODAING ITEM GUI : " << m_renderedSlotItems.size() << std::endl;
		}
	}

	void InventoryContainerRenderer::clickSlot(uint8_t index)
	{
		//Slot is a player inventory representation.
		if (index >= m_currentContainer->GetSize())
		{
			Inventory::ReturnItem retItem = TestGame::ThePlayer->GetInventory()->GetItem(index - m_currentContainer->GetSize());
			if (retItem.ri_IsNull) { return; }
			//Attempt to add the item from the player inventory to the current open inventory.
			if (m_currentContainer->AddItem(retItem.ri_Item) != -1)
			{
				std::cout << "ADDED ITEM\n";
				//If success, remove the item from the players inventory.
				TestGame::ThePlayer->GetInventory()->SetItem(index - m_currentContainer->GetSize(), nullptr);
			}
		}
		else 
		{
			Inventory::ReturnItem retItem = m_currentContainer->GetItem(index);
			if (retItem.ri_IsNull) { return; }

			if (TestGame::ThePlayer->GetInventory()->AddItem(retItem.ri_Item) != -1)
			{
				m_currentContainer->SetItem(index, nullptr);
			}
		}

		/*
			Refresh the current inventory.
		*/

		InventoryContainer* const lastContainer = m_currentContainer;

		lastContainer->CloseGUI();
		lastContainer->OpenGUI();
	}

	
	void InventoryContainerRenderer::updateTooltip(uint8_t index, bool clearTooltip)
	{
		if (clearTooltip)
		{
			m_hidingTooltip = true;

			if (m_tooltip != nullptr)
			{
				if (m_tooltip->GetScale().Y > 0.05f)
				{
					//Scale down the tool tip by 2% until it has a height less than 0.05.
					m_tooltip->SetScale({ m_tooltip->GetScale().X, m_tooltip->GetScale().Y - (m_tooltip->GetScale().Y * TOOLTIP_ANIMATION_SPEED) });
				}
				else
				{
					//Tooltip is close to small enough, but will never actually reach 0 so set it to 0.
					m_tooltip->SetScale({ m_tooltip->GetScale().X, 0 });
				}
				m_tooltip->SetPosition(InputManager::GetMouseScreenPosition() - Vec2{ 0, m_tooltip->GetScale().Y });
			}

			return;
		}

		if (m_tooltip == nullptr) { return; }

		m_hidingTooltip = false;

		if (m_tooltip->GetScale().Y < TOOLTIP_HEIGHT)
		{
			//Scale up the tooltip until it reaches the objective TOOLTIP_HEIGHT.
			m_tooltip->SetScale({ m_tooltip->GetScale().X, m_tooltip->GetScale().Y + (TOOLTIP_HEIGHT - m_tooltip->GetScale().Y) * TOOLTIP_ANIMATION_SPEED });
		}
		else {
			m_tooltip->SetScale({ m_tooltip->GetScale().X, TOOLTIP_HEIGHT });
		}

		m_tooltip->SetPosition(InputManager::GetMouseScreenPosition() - Vec2{ 0, m_tooltip->GetScale().Y });
	}
}
