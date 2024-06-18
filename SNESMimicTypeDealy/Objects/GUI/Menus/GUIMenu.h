#pragma once

#include <string>
#include <functional>
#include <mutex>

#define LoadMenuW LoadMenu
namespace GAME_NAME::Objects::GUI::Menus
{
	class GUIMenu
	{
	public:
		static unsigned int LoadMenu(const char* menu, std::function<void(int)>* elementCallback);

		static void RemoveLastMenu();

		inline static void AddLastMenuObject(uint8_t layer, int count = 1)
		{
			m_asyncAddLock.lock();
			m_lastMenuObjects[layer] += count;
			m_asyncAddLock.unlock();
		}

		inline static void AddLastRegisterButtonID(unsigned int id)
		{
			m_asyncAddLock.lock();
			m_lastRegisteredButtonIds.push_back(id);
			m_asyncAddLock.unlock();
		}
	protected:
		static uint8_t m_menusOpen;
		static uint16_t m_lastMenuObjects[3];
		static std::vector<unsigned int> m_lastRegisteredButtonIds;

		static std::mutex m_asyncAddLock;
	};
}