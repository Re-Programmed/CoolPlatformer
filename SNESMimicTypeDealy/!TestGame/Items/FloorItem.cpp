#include "FloorItem.h"
#include "../../Input/InputManager.h"

namespace GAME_NAME
{
	namespace Items
	{
		FloorItem::FloorItem(Vec2 position, ITEM_TYPE type)
			: ActiveRotationalBoxCollisionGravityObject(position, Vec2(DF_FLOOR_ITEM_SCALE), ITEMTYPE_GetItemTypeTexture(type), RotationalCollider_Settings(
				53.0f,		//Bounce
				3.25f,		//Rotation Effect
				7.50f		//Gravity Rotation Effect
			)), m_inventoryItem(InventoryItem(type))
		{
			m_physics->SetGravityStrength(m_physics->GetGravityStrength() * 7);
		}

		FloorItem::FloorItem(Vec2 position, InventoryItem &item)
			: ActiveRotationalBoxCollisionGravityObject(position, Vec2(DF_FLOOR_ITEM_SCALE), ITEMTYPE_GetItemTypeTexture(item.GetType()), RotationalCollider_Settings(
				53.0f,		//Bounce
				3.25f,		//Rotation Effect
				7.50f		//Gravity Rotation Effect
			)), m_inventoryItem(item)
		{
			m_physics->SetGravityStrength(m_physics->GetGravityStrength() * 7);
		}

		void FloorItem::Update(GLFWwindow* window)
		{
			ActiveRotationalBoxCollisionGravityObject::Update(window);
		}
	}
}