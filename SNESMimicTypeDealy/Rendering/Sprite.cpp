#include "Sprite.h"
#include "Window.h"

namespace GAME_NAME
{

	namespace Rendering
	{
		Vec2 Sprite::m_resolutionScale = Vec2::One;

		void Sprite::Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale, float rotation)
		{
			glBindTexture(GL_TEXTURE_2D, m_spriteId);
			glLoadIdentity();
			glTranslatef((position.X - cameraPosition.X) * m_resolutionScale.X, (position.Y - cameraPosition.Y) * m_resolutionScale.Y, 0);

			glScalef(scale.X * m_resolutionScale.X, scale.Y * m_resolutionScale.Y, 1.f);

			glRotatef(rotation, 0, 0, 0);
			glDrawArrays(GL_QUADS, 0, 4);

		}

		void Sprite::SetResolution(Vec2 res)
		{
			m_resolutionScale = Vec2(res.X / TargetResolutionX, res.Y / TargetResolutionY);
		}

		const unsigned int Sprite::GetSpriteId()
		{
			return m_spriteId;
		}

		std::string Sprite::ToString()
		{
			return "Sprite {" + std::to_string(this->m_spriteId) + "}";
		}

	}
}