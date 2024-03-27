#include "FrontWall.h"

#include "../../../../Rendering/DynamicSprite.h"

#define FADE_INCREMENT 0.02f

namespace GAME_NAME::Objects::Environment::Buildings
{
	FrontWall::FrontWall(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float baseOpacity)
		: GameObject(position, scale, sprite),
		m_baseOpacity(baseOpacity), m_isClear(false)
	{

	}

	void FrontWall::Render(const Vec2 cameraPosition)
	{
		if (m_opacity >= 1.f) { GameObject::Render(cameraPosition); }

		if (m_isClear)
		{
			if (m_opacity > 0.f)
			{
				m_opacity -= FADE_INCREMENT;
			}
			else {
				return;
			}
		}
		else {
			if (m_opacity < m_baseOpacity)
			{
				m_opacity += FADE_INCREMENT;
			}
		}

		Rendering::DynamicSprite ds(m_sprite->GetSpriteId());

		Vec4 color[4] {
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity)
		};

		ds.UpdateTextureColor(color);

		ds.Render(cameraPosition, m_position, m_scale, m_rotation);
		
	}

	void FrontWall::Update(GLFWwindow* window)
	{
		
	}
}