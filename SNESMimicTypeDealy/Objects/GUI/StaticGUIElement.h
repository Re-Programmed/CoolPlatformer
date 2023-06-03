#pragma once
#include "../../Utils/Math/Vec2.h"
#include "../../Rendering/Sprite.h"
#include "IGUIElement.h"

namespace GAME_NAME
{
	using namespace MathUtils;
	namespace Objects
	{
		namespace GUI
		{
			/// <summary>
			/// A GUI element that will not move.
			/// </summary>
			class StaticGUIElement : public IGUIElement

			{
			public:
				StaticGUIElement(Vec2 position, Vec2 scale, GLuint texture)
					:m_position(position), m_scale(scale), m_texture(texture)
				{
					
				}

				/// <summary>
				/// Draw the element.
				/// </summary>
				void Render();
			private:
				const Vec2 m_position;
				const Vec2 m_scale;
				const GLuint m_texture;
			};
		}
	}
}