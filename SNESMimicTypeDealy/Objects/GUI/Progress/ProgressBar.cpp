#include "ProgressBar.h"

namespace GAME_NAME::Objects::GUI
{
	void ProgressBar::SetPercentage(char percentage)
	{
		m_percentage = percentage;

		Vec2 textureCoords[4]{
			Vec2(0.f, 0.f),
			Vec2(0.f, 1.f),
			Vec2(((float)percentage) / 100.f, 1.f),
			Vec2(((float)percentage) / 100.f, 0.f)
		};

		m_sprite = new DynamicSprite(m_sprite->GetSpriteId(), textureCoords, textureCoords);
	}


	
}

