#pragma once
#ifndef _GUI_BUTTON
#define _GUI_BUTTON
#include "../../Utils/Math/Vec2.h"
#include "../../Rendering/Sprite.h"
#include "StaticGUIElement.h"
#include <functional>

namespace GAME_NAME
{
	using namespace MathUtils;
	namespace Objects
	{
		namespace GUI
		{
			/// <summary>
			/// A GUI element that will not update.
			/// </summary>
			class GUIButton : public StaticGUIElement

			{
			public:
				GUIButton(Vec2 position, Vec2 scale, GLuint texture, std::function<void(int)>* onClick)
					:StaticGUIElement(position, scale, texture), OnClick(onClick), m_buttonId(-1)
				{

				}

				GUIButton(Vec2 position, Vec2 scale, GLuint texture, std::function<void(int)>* onClick, int buttonId)
					:StaticGUIElement(position, scale, texture), OnClick(onClick), m_buttonId(buttonId)
				{

				}

				std::function<void(int buttonId)>* OnClick;

				inline void SetButtonId(unsigned int id)
				{
					m_buttonId = id;
				}

				inline int GetButtonId()
				{
					return m_buttonId;
				}

			private:
				unsigned int m_buttonId;

			};
		}
	}
}
#endif