#include "StaticGUIElement.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace GUI
		{
			
			void StaticGUIElement::Render()
			{
				m_sprite->Render(Vec2::Zero, m_position, m_scale, 0.0f);
			}
			
		}
	}
}