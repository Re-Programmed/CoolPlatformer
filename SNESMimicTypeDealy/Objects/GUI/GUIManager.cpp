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

			void GUIManager::ButtonClickEvent(Vec2 position)
			{
				for (GUIButton* gb : m_buttons)
				{
					if (Utils::CollisionDetection::PointWithinBoxBL(position, gb->GetPosition(), gb->GetScale()))
					{
						gb->OnClick(gb->GetButtonId());
					}
				}
			}
		}
	}
}