#include "GUIMenu.h"

#include "../../../Settings/SettingsGlobals.h"
#include "../../../Resources/AssetManager.h"
#include <fstream>
#include <thread>

#if _DEBUG
#include "../../../Debug/DebugLog.h"
#endif

#include "../GUIManager.h"
#include "../Progress/ProgressBar.h"

#define LoadMenuW LoadMenu

namespace GAME_NAME::Objects::GUI::Menus
{
	uint8_t GUIMenu::m_menusOpen = 0;

	uint16_t GUIMenu::m_lastMenuObjects[3] = {
		0,0,0
	};

	std::vector<unsigned int> GUIMenu::m_lastRegisteredButtonIds;

	void GUIMenu_loadMenuObjectThread(std::string line, std::function<void(int)>* elementCallback)
	{
#if _DEBUG
		DEBUG::DebugLog::Log("[Menu] Loading object with string \"" + line + "\".");
#endif

		std::string typeCode = std::string(line).erase(3, line.length());
		GUIManager::GUI_ELEMENT_TYPE gtype = GUIManager::GetGUIComponentFromCode(typeCode);

		std::stringstream ComponentStream(std::string(line).erase(0, 4));
		std::string component;
		std::vector<std::string> data;

		while (std::getline(ComponentStream, component, ','))
		{
			if (component.ends_with("sb"))
			{
				component.erase(component.size() - 2, component.size());
				component = std::to_string(SpriteBase(std::stoi(component)));
			}

			data.push_back(component);
		}

		switch (gtype)
		{
			case GUIManager::EL_TEXT:
				break;
			case GUIManager::EL_BUTTON:
			{
				GUIButton* gButton = new GUIButton(Vec2(std::stoi(data[0]), std::stoi(data[1])), Vec2(std::stoi(data[2]), std::stoi(data[3])), Renderer::GetSprite(std::stoi(data[4]))->GetSpriteId(), elementCallback, std::stoi(data[5]));
				Renderer::LoadGUIElement(gButton);

				GUIMenu::AddLastRegisterButtonID(GUIManager::RegisterButton(gButton));
				GUIMenu::AddLastMenuObject(1);
				break;
			}
			///Creates an EL_BLANK (pos1, pos2, sca1, sca2, sprite, layer)
			case GUIManager::EL_BLANK:
			{
				StaticGUIElement* gBlank = new StaticGUIElement(Vec2(std::stoi(data[0]), std::stoi(data[1])), Vec2(std::stoi(data[2]), std::stoi(data[3])), Renderer::GetSprite(std::stoi(data[4]))->GetSpriteId());
				Renderer::LoadGUIElement(gBlank, std::stoi(data[5]));

				GUIMenu::AddLastMenuObject(std::stoi(data[5]));
				break;
			}
			case GUIManager::EL_PROGRESS:
			{
				ProgressBar* pBar = new ProgressBar(Vec2(std::stoi(data[0]), std::stoi(data[1])), Vec2(std::stoi(data[2]), std::stoi(data[3])), Renderer::GetSprite(std::stoi(data[4]))->GetSpriteId(), std::stoi(data[5]));
				Renderer::LoadGUIElement(pBar);

				GUIMenu::AddLastMenuObject(1);
				break;
			}
		}
	}

	unsigned int GUIMenu::LoadMenu(const char* menu, std::function<void(int)>* elementCallback)
	{
		GUIManager::MenuIsOpen = true;
		m_menusOpen++;

		m_lastMenuObjects[0] = 0; m_lastMenuObjects[1] = 0; m_lastMenuObjects[2] = 0;
		m_lastRegisteredButtonIds.clear();

		std::string filePath = AssetPath;
		filePath += MenuSubfolder;
		filePath += menu;
		filePath += MenuFileExtension;

		std::ifstream MenuStream(filePath);
		std::string line;

		std::vector<std::thread*> threads;
		uint16_t thCurr = 0;

		while (std::getline(MenuStream, line, '\n'))
		{
			if (line.empty() || line.starts_with(";")) { continue; } //For line breaks or lines beginning with a ";" do nothing. (useful for comments etc.)

			threads.push_back(new std::thread(GUIMenu_loadMenuObjectThread, line, elementCallback));
			thCurr++;

		checkthreads:
			if (thCurr == AppData::Settings::SettingsGlobals::MaxThreads.Value)
			{
				for (int i = 0; i < thCurr; i++)
				{
					if (threads[i] != nullptr && threads[i]->joinable())
					{
						threads[i]->join();
						//delete threads[i];
					}
				}

				thCurr = 0;
			}
		}

		for (int i = 0; i < thCurr; i++)
		{
			if (threads[i] != nullptr && threads[i]->joinable())
			{
				threads[i]->join();
				//delete threads[i];
			}
		}

		return m_lastRegisteredButtonIds.size() == 0 ? 0 : m_lastRegisteredButtonIds[0];
	}

	void GUIMenu::RemoveLastMenu()
	{
		m_menusOpen--;

		if (m_menusOpen == 0)
		{
			GUIManager::MenuIsOpen = false;
		}

		for (int i = 0; i < 3; i++)
		{
			if (m_lastMenuObjects[i] > 0)
			{
				Renderer::ClearGUIObjects(m_lastMenuObjects[i], i);
			}
		}

		for (unsigned int i : m_lastRegisteredButtonIds)
		{
			GUIManager::UnregisterButton(i);
		}
	}

}

