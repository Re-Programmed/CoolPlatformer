#pragma once

#ifndef _GUI_MANAGER
#define _GUI_MANAGER
#include "../../Utils/Math/Vec2.h"
#include <vector>
#include "GUIButton.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace GUI
		{
			using namespace MathUtils;
			/// <summary>
			/// Used for determining GUI events such as button presses.
			/// </summary>
			class GUIManager
			{
			public:
				/// <summary>
				/// Call this everytime a click occurs. Updates all buttons accordingly.
				/// </summary>
				static void ButtonClickEvent(Vec2 position);

				/// <summary>
				/// Register a button so it can get clicked.
				/// </summary>
				/// <param name="btn"></param>
				/// <returns></returns>
				static inline unsigned int RegisterButton(GUIButton* btn)
				{
					m_buttons.push_back(btn);
					btn->SetButtonId(m_buttons.size() - 1);
					return m_buttons.size() - 1;
				}

				/// <summary>
				/// Always unregister buttons before deleting them.
				/// </summary>
				/// <param name="index"></param>
				static inline void UnregisterButton(unsigned int index)
				{
					m_buttons.erase(m_buttons.begin() + index);
				}

				static inline void UnregisterButton(GUIButton* btn)
				{
					m_buttons.erase(m_buttons.begin() + btn->GetButtonId());
				}

			private:
				/// <summary>
				/// All buttons on screen.
				/// </summary>
				static std::vector<GUIButton*> m_buttons;
			};
		}
	}
}
#endif