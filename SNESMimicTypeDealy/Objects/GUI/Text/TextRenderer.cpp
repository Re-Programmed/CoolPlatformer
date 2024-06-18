#include "TextRenderer.h"

#include "../../../Rendering/Renderers/Renderer.h"

#include "../../../EngineCompileOptions.h"
#include <algorithm>

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

	TextRenderer::Letter TextRenderer::RenderLetter(char letter, const Vec2& position, const float scale, int layer)
	{
		int texture = GLOBAL_SPRITE_BASE;

		for (int i = 0; i < VALID_CHARS_LENGTH; i++)
		{
			if (letter >= m_validWordChars[i].StartLetter && letter <= m_validWordChars[i].EndLetter)
			{
				texture = DEFAULT_FONT_RENDER_A_SPRITE_ID + m_validWordChars[i].Offset + (letter - m_validWordChars[i].StartLetter);
				break;
			}
		}

		if (texture == GLOBAL_SPRITE_BASE) { return nullptr; }

		std::cout << "Rendering a Letter: " + texture;
		StaticGUIElement* GUIelement = new StaticGUIElement(position, { -scale, scale }, Renderer::GetSprite(texture)->GetSpriteId());
		Letter letterObject(GUIelement);

		Renderer::LoadGUIElement(GUIelement, layer);

		return letterObject;
	}

	TextRenderer::RenderedWord TextRenderer::RenderWord(std::string word, Vec2 position, const float scale, const float&& digitPadding, int layer)
	{
		//Convert entire word string to lowercase.
		std::transform(word.begin(), word.end(), word.begin(), [](unsigned char l) {
			return std::tolower(l);
		});

		RenderedWord wordRet;

		for (size_t i = 0; i < word.size(); i++)
		{
			Letter letter = RenderLetter(word.at(i), position + Vec2{ i * (scale + digitPadding), 0 }, scale, layer);
			if (letter == nullptr) { continue; }
			wordRet.push_back(letter);
		}

		return wordRet;
	}
}