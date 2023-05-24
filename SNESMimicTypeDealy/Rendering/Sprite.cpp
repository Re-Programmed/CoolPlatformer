#include "Sprite.h"

namespace GAME_NAME
{

	namespace Rendering
	{
		void Sprite::Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale)
		{
			glBindTexture(GL_TEXTURE_2D, m_spriteId);

			glLoadIdentity();
			glTranslatef(position.X - cameraPosition.X, position.Y - cameraPosition.Y, 0);

			glScalef(scale.X, scale.Y, 1);

			glDrawArrays(GL_QUADS, 0, 4);
		}

		std::string Sprite::ToString()
		{
			return "Sprite {" + std::to_string(this->m_spriteId) + "}";
		}

	}
}