#include "ProgressBar.h"

namespace GAME_NAME::Objects::GUI
{
	void ProgressBar::SetPercentage(char percentage, bool ignoreSmoothing)
	{
		m_percentage = percentage;

		m_percentage = percentage;

		if (ignoreSmoothing)
		{
			//Update display percentage to force smoothing function to update the slightest amount.
			m_displayPercentage = m_percentage - 0.01f;
		}
	}

	void ProgressBar::Render(float zoom)
	{
		if (m_percentage != m_displayPercentage)
		{
			//Save the sprite ID as m_sprite will be deleted.
			const unsigned int retrievedSpriteID = m_sprite->GetSpriteId();
			delete m_sprite;

			//Smoothly update display percentage.
			m_displayPercentage = (float)std::lerp(m_displayPercentage, m_percentage, 0.01f);


			Vec2 textureCoords[4]{
				Vec2(0.f, 0.f),
				Vec2(0.f, 1.f),
				Vec2(((float)m_displayPercentage) / 100.f, 1.f),
				Vec2(((float)m_displayPercentage) / 100.f, 0.f)
			};

			m_sprite = new DynamicSprite(retrievedSpriteID, textureCoords, textureCoords);
		}

		StaticGUIElement::Render(zoom);
	}


	
}

