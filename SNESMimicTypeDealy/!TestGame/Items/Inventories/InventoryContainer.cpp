#include "InventoryContainer.h"
#include <cstdarg>
namespace GAME_NAME::Items::Inventories
{
	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation)
		: Inventory(name, size), GameObject(position, scale, sprite, rotation)
	{

	}

	InventoryContainer::InventoryContainer(std::string name, size_t size, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation, int itemCount, ...)
		: Inventory(name, size), GameObject(position, scale, sprite, rotation)
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
		m_isOpen = true;
	}

	void InventoryContainer::CloseGUI()
	{
		m_isOpen = false;
	}

}
