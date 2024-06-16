#pragma once

#include <string>
#include "../../../Utils/Math/Vec2.h"
#include "../../../Rendering/Sprite.h"
#include <vector>
#include "../../../Objects/GUI/StaticGUIElement.h"

#define DREND_FILE_PREFIX "/gui_text"

namespace GAME_NAME::Objects::GUI::Text
{
	using namespace MathUtils;

	class TextRenderer
	{
	public:
		typedef unsigned char digit;

		typedef std::vector<StaticGUIElement*> RenderedDigit;

		typedef std::shared_ptr<StaticGUIElement> Letter;
		typedef std::vector<Letter> RenderedWord;


		/// <summary>
		/// Draws a digit to the screen at the given position with the given scale.
		/// </summary>
		/// <param name="digit">Digit must be less than 10.</param>
		/// <param name="position">The position to draw the digit.</param>
		/// <param name="scale">The scale to draw the digit.</param>
		/// <returns></returns>
		static StaticGUIElement* RenderDigit(digit digit, Vec2& position, const float scale);

		static RenderedDigit RenderNumber(uint16_t number, Vec2& firstDigitPosition, const float scale, const float digitPadding, uint8_t minimumDigits = 0);

		static Letter RenderLetter(char letter, const Vec2& position, const float scale);

		static RenderedWord RenderWord(std::string& word, Vec2& position, const float scale, const float&& digitPadding);
	};
}