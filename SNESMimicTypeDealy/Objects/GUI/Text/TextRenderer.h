#pragma once

#include <string>
#include "../../../Utils/Math/Vec2.h"
#include "../../../Rendering/Sprite.h"

#define DREND_FILE_PREFIX "/gui_text"

namespace GAME_NAME::Objects::GUI::Text
{
	using namespace MathUtils;

	class TextRenderer
	{
	public:
		typedef unsigned char digit;

		static void RenderDigit(digit digit, Vec2& position, Vec2& scale);

		/// <summary>
		/// Assign a digit to a sprite, must be called before rendering any digits.
		/// </summary>
		/// <param name="sprite">The sprite to give this digit.</param>
		/// <param name="d">Which digit to assign this sprite to.</param>
		inline static void AssignDigitSprite(Rendering::Sprite* sprite, digit d)
		{
			m_digitSprites[d] = sprite;
		}
	private:
		static Rendering::Sprite* m_digitSprites[10];
	};
}