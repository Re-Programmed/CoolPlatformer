#include "StaticGUIElement.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace GUI
		{
			
			void StaticGUIElement::Render()
			{
				glBindTexture(GL_TEXTURE_2D, m_texture);

				glLoadIdentity();
				glTranslatef(m_position.X, m_position.Y, 0.f);
				glScalef(m_scale.X, m_scale.Y, 1.f);

				//Texture coords somehow for masking

				glDrawArrays(GL_QUADS, 0, 4);
			}
			
		}
	}
}