#include "GUIManager.h"
#include "../../Utils/CollisionDetection.h"
#pragma once

namespace GAME_NAME
{
	namespace Objects
	{
		namespace GUI
		{
			std::vector<GUIButton*> GUIManager::m_buttons;

			GUIManager::GUI_ELEMENT_TYPE GUIManager::GetGUIComponentFromCode(std::string code)
			{
				for (int i = 0; i < GUIMANAGER_M_ELEMENT_CODES_LENGTH; i++)
				{
					if (m_elementCodes[i] == code)
					{
						return (GUIManager::GUI_ELEMENT_TYPE)i;
					}
				}

				return GUIManager::EL_BLANK;
			}

			void GUIManager::ButtonClickEvent(Vec2 position)
			{
				for (GUIButton* gb : m_buttons)
				{
					if (Utils::CollisionDetection::PointWithinBoxBL(position, gb->GetPosition(), gb->GetScale()))
					{
						(*gb->OnClick)(gb->GetButtonId());
						return;
					}
				}
			}
		}
	}
}