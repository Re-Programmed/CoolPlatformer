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
#define GUIMANAGER_M_ELEMENT_CODES_LENGTH 5
				/// <summary>
				/// Types of GUI elements that can be created.
				/// </summary>
				enum GUI_ELEMENT_TYPE
				{
					EL_TEXT,		//Text object.
					EL_BUTTON,		//Clickable button.
					EL_NUM,			//Number display.
					EL_BLANK,		//Object with texture.
					EL_PROGRESS		//Progress Bar.
				};
				
			private:
				static inline const std::string m_elementCodes[GUIMANAGER_M_ELEMENT_CODES_LENGTH] {
					"txt",
					"btn",
					"num",
					"obj",
					"prg"
				};

			public:

				static inline bool MenuIsOpen = false;

				/// <summary>
				/// Returns the GUI element type based on the given code.
				/// </summary>
				static GUI_ELEMENT_TYPE GetGUIComponentFromCode(std::string code);

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
					btn->SetButtonId(static_cast<unsigned int>(m_buttons.size()) - 1);
					return static_cast<unsigned int>(m_buttons.size()) - 1;
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
					for (int i = 0; i < m_buttons.size(); i++)
					{
						if (m_buttons[i] == btn)
						{
							m_buttons.erase(m_buttons.begin() + i);
							return;
						}
					}
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