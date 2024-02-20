#include "TextRenderer.h"

#include "../../../Rendering/Renderers/Renderer.h"

#include "../../../EngineCompileOptions.h"

namespace GAME_NAME::Objects::GUI::Text
{
	StaticGUIElement* TextRenderer::RenderDigit(digit digit, Vec2& position, const float scale)
	{
		int texture = TEXT_RENDERER_ZERO_DIGIT_SPRITE_ID + (int)digit;
		StaticGUIElement* go = new StaticGUIElement(position, Vec2(-TEXT_RENDERER_DIGIT_SIZE_X * scale, TEXT_RENDERER_DIGIT_SIZE_Y * scale), Renderer::GetSprite(texture)->GetSpriteId());

		Renderer::LoadGUIElement(go, 1);

		return go;
	}

	GAME_NAME::Objects::GUI::Text::TextRenderer::RenderedDigit TextRenderer::RenderNumber(uint16_t number, Vec2& firstDigitPosition, const float scale, const float digitPadding)
	{
		RenderedDigit finalDigit;

		uint8_t currentDigit = 0;
		while (number > 0)
		{
			Vec2 pos(firstDigitPosition.X + (currentDigit * (TEXT_RENDERER_DIGIT_SIZE_X + digitPadding)), firstDigitPosition.Y);
		
			finalDigit.push_back(RenderDigit(number % 10, pos, scale));

			number /= 10;
			currentDigit++;
		}

		return finalDigit;
	}
}