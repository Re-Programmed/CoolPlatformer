#pragma once

#include <string>
#include <functional>

#define LoadMenuW LoadMenu
namespace GAME_NAME::Objects::GUI::Menus
{
	class GUIMenu
	{
	public:
		static unsigned int LoadMenu(const char* menu, std::function<void(int)>* elementCallback);

		static void RemoveLastMenu();

		inline static void AddLastMenuObject(uint8_t layer)
		{
			m_lastMenuObjects[layer]++;
		}

		inline static void AddLastRegisterButtonID(unsigned int id)
		{
			m_lastRegisteredButtonIds.push_back(id);
		}
	protected:
		static uint8_t m_menusOpen;
		static uint16_t m_lastMenuObjects[3];
		static std::vector<unsigned int> m_lastRegisteredButtonIds;
	};
}