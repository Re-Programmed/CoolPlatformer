#pragma once
#include "../../Components/Physics/Collision/Helpers/ActiveRotationalBoxCollisionGravityObject.h"
#include "InventoryItem.h"

#define DF_FLOOR_ITEM_SCALE 8u
namespace GAME_NAME
{
	namespace Items
	{
		using namespace Objects;
		using namespace Components::Physics::Collision;

		/// <summary>
		/// A floor item represents an item that has been dropped on the ground.
		/// </summary>
		class FloorItem : public Components::Physics::Collision::ActiveRotationalBoxCollisionGravityObject
		{

		public:
			/// <summary>
			/// Create a FloorItem with position and data.
			/// </summary>
			/// <param name="position">Where the floor item is.</param>
			/// <param name="item">What item the floor item is.</param>
			FloorItem(Vec2 position, InventoryItem &item, float pickupDelay = 0);

			FloorItem(Vec2 position, ITEM_TYPE type, float pickupDelay = 0);

			~FloorItem();

			void Update(GLFWwindow* window) override; 

		protected:
			void pickup();

		private:

			/// <summary>
			/// The contained item by this floor item.
			/// </summary>
			const InventoryItem m_inventoryItem;

			const float m_pickupDelay;
			float m_lifetime;

			bool m_pickedUp = false;
		};
	}
}