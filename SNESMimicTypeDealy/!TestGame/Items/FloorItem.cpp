#include "FloorItem.h"
#include "../../Input/InputManager.h"
#include "../../Utils/Time/GameTime.h"
#include "../TestGame.h"

namespace GAME_NAME
{
	namespace Items
	{
		FloorItem::FloorItem(Vec2 position, ITEM_TYPE type, float pickupDelay)
			: ActiveRotationalBoxCollisionGravityObject(position, Vec2(DF_FLOOR_ITEM_SCALE), ITEMTYPE_GetItemTypeTexture(type), RotationalCollider_Settings(
				53.0f,		//Bounce
				3.25f,		//Rotation Effect
				7.50f		//Gravity Rotation Effect
			)), m_inventoryItem(InventoryItem(type)), m_lifetime(0), m_pickupDelay(pickupDelay)
		{
			m_physics->SetGravityStrength(m_physics->GetGravityStrength() * 7);
		}

		FloorItem::~FloorItem()
		{
			ActiveRotationalBoxCollisionGravityObject::~ActiveRotationalBoxCollisionGravityObject();
		}

		FloorItem::FloorItem(Vec2 position, InventoryItem &item, float pickupDelay)
			: ActiveRotationalBoxCollisionGravityObject(position, Vec2(DF_FLOOR_ITEM_SCALE), ITEMTYPE_GetItemTypeTexture(item.GetType()), RotationalCollider_Settings(
				53.0f,		//Bounce
				3.25f,		//Rotation Effect
				7.50f		//Gravity Rotation Effect
			)), m_inventoryItem(item), m_lifetime(0), m_pickupDelay(pickupDelay)
		{
			m_physics->SetGravityStrength(m_physics->GetGravityStrength() * 7);
		}

		void FloorItem::Update(GLFWwindow* window)
		{
			//Check if the item has been picked up.
			if (m_pickedUp) { return; }

			//Track the lifetime of the item for pickup delay.
			m_lifetime += Utils::Time::GameTime::GetScaledDeltaTime();

			if (m_lifetime >= m_pickupDelay)
			{
				if (Vec2::Distance(TestGame::ThePlayer->GetPosition(), m_position) < m_scale.X/2.f)
				{
					pickup();
				}
			}

			ActiveRotationalBoxCollisionGravityObject::Update(window);
		}

		void FloorItem::pickup()
		{
			//Attempt to add the item to the player's inventory.
			if (TestGame::ThePlayer->GetInventory()->AddItem(InventoryItem(this->m_inventoryItem)) >= 0)
			{
				//Sucessful, destroy the item.
				m_pickedUp = true;
				Renderer::DestroyActiveObjectImmediate(this);
				//delete this;
			}
		}
	}
}