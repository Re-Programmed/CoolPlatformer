#include "../Inventory.h"
#include "../../../Objects/GameObject.h"

namespace GAME_NAME::Items::Inventories
{
	class InventoryContainer
		: public Inventory, public GameObject
	{
	public:
		InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation = 0.f);
		InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation, int itemCount, ...);

		void OpenGUI();
		void CloseGUI();

		inline bool GetOpen()
		{
			return m_isOpen;
		}
	private:
		bool m_isOpen = false;
	};
}