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
			/// A GUI element that will not update.
			/// </summary>
			class StaticGUIElement : public IGUIElement

			{
			public:
				StaticGUIElement(Vec2 position, Vec2 scale, GLuint texture)
					:m_position(position), m_scale(scale), m_texture(texture)
				{
					
				}

#pragma region Modifier Funcs


				inline void SetPosition(Vec2 position)
				{
					m_position = position;
				}

				inline void SetScale(Vec2 scale)
				{
					m_scale = scale;
				}

				inline Vec2 GetPosition()
				{
					return m_position;
				}

				inline Vec2 GetScale()
				{
					return m_scale;
				}

				inline void SetTexture(GLuint texture)
				{
					m_texture = texture;
				}

				inline GLuint GetTexture()
				{
					return m_texture;
				}
#pragma endregion


				/// <summary>
				/// Draw the element.
				/// </summary>
				void Render();
			private:
				Vec2 m_position;
				Vec2 m_scale;
				GLuint m_texture;
			};
		}
	}
}