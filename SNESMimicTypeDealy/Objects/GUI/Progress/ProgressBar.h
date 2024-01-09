#pragma once

#include "../StaticGUIElement.h"

namespace GAME_NAME::Objects::GUI
{

	using namespace MathUtils;

	class ProgressBar
		: public StaticGUIElement
	{
	public:
		ProgressBar(Vec2 position, Vec2 scale, GLuint texture)
			:StaticGUIElement(position, scale, texture)
		{
			SetPercentage(100);
		}

		ProgressBar(Vec2 position, Vec2 scale, GLuint texture, char percentage)
			:StaticGUIElement(position, scale, texture)
		{
			SetPercentage(percentage);
		}

		void SetPercentage(char percentage);

		inline char GetPercentage()
		{
			return m_percentage;
		}

	private:
		char m_percentage;
	};
}