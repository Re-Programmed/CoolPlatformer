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

	GAME_NAME::Objects::GUI::Text::TextRenderer::RenderedDigit TextRenderer::RenderNumber(uint16_t number, Vec2& firstDigitPosition, const float scale, const float digitPadding, uint8_t minimumDigits)
	{
		RenderedDigit finalDigit;

		uint8_t currentDigit = 0;
		while (number > 0)
		{
			for (StaticGUIElement* sge : finalDigit)
			{
				sge->SetPosition(sge->GetPosition() + Vec2(TEXT_RENDERER_DIGIT_SIZE_X + digitPadding, 0));
			}

			Vec2 pos(firstDigitPosition.X, firstDigitPosition.Y);
		
			finalDigit.push_back(RenderDigit(number % 10, pos, scale));

			number /= 10;
			currentDigit++;
			if(minimumDigits > 0){ minimumDigits--; }
		}

		while (minimumDigits > 0)
		{
			for (StaticGUIElement* sge : finalDigit)
			{
				sge->SetPosition(sge->GetPosition() + Vec2(TEXT_RENDERER_DIGIT_SIZE_X + digitPadding, 0));
			}

			Vec2 pos(firstDigitPosition.X, firstDigitPosition.Y);
			finalDigit.push_back(RenderDigit(0, pos, scale));
			minimumDigits--;
		}
		
		return finalDigit;
	}

	TextRenderer::Letter TextRenderer::RenderLetter(char letter, const Vec2& position, const float scale)
	{
		int texture = DEFAULT_FONT_RENDER_A_SPRITE_ID + (letter - 'a');
		std::cout << "Rendering a Letter: " + texture;
		Letter letterObject(new StaticGUIElement(position, scale, Renderer::GetSprite(texture)->GetSpriteId()));

		Renderer::LoadGUIElement(letterObject.get());

		return letterObject;
	}

	TextRenderer::RenderedWord TextRenderer::RenderWord(std::string& word, Vec2& position, const float scale, const float&& digitPadding)
	{
		RenderedWord wordRet;

		for (size_t i = 0; i < word.size(); i++)
		{
			wordRet.push_back(RenderLetter(word.at(i), position + Vec2{ i * (scale + digitPadding), 0}, scale));
		}

		return wordRet;
	}
}