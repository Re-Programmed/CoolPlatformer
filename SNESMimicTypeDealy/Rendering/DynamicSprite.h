#pragma once
#include "Sprite.h"
#include "../Utils/Math/Vec4.h"

namespace GAME_NAME
{
	namespace Rendering
	{
		//A sprite that can change its vertices, texture coordinates, and texture colors.
		class DynamicSprite
			: public Sprite
		{
		public:
			DynamicSprite(Sprite& sprite);
			DynamicSprite(const unsigned int spriteId);
			DynamicSprite(const unsigned int spriteId, Vec2 vertices[4]);
			DynamicSprite(const unsigned int spriteId, Vec2 vertices[4], Vec2 textureCoords[4]);
			DynamicSprite(const unsigned int spriteId, Vec2 vertices[4], Vec2 textureCoords[4], Vec4 textureColor[4]);

			~DynamicSprite();

			void UpdateVertices(Vec2 verts[4]);

			void Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale, float rotation = 0.f) override;
		private:
			Vec2 m_vertices[4];
			Vec2 m_textureCoords[4];
			Vec4 m_textureColor[4];
		};

	}
}