#include "GlitchedRegion.h"


#define DEBUG_RENDER_GLITCHED_AREAS false

namespace GAME_NAME::Objects
{
	int GlitchedRegion::m_spriteCountBeforePixelated = -1;

	GlitchedRegion::GlitchedRegion(Vec2 position, Vec2 scale)
#if DEBUG_RENDER_GLITCHED_AREAS
		: GameObject(position, scale,  Renderer::GetSprite(SpriteBase(101)))
#else
		: GameObject(position, scale, nullptr)
#endif
	{
		//Convert all objects within to "8-bit."

		if (m_spriteCountBeforePixelated < 0)
		{
			const unsigned int& spriteCount = Renderer::GetImageCount() - 1;
			m_spriteCountBeforePixelated = spriteCount;
			
			for (int i = 1; i <= spriteCount; i++)
			{
				Renderer::TextureData data = Renderer::GetTextureData(i, 0);

				//Modify the texture data.

				unsigned char* newData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * (data.Width * data.Height * 4)));

				int newPixel = 0;
				for (int pixel = 0; pixel < data.Width * data.Height * 4; pixel += 8)
				{
					newData[newPixel++] = data.Data[pixel];
					newData[newPixel++] = data.Data[pixel + 1];
					newData[newPixel++] = data.Data[pixel + 2];
					newData[newPixel++] = data.Data[pixel + 3];

					if ((pixel + 8) % (data.Width * 4) == 0)
					{
						pixel += data.Width * 4;
					}
				}

				//End modify the texture data.

				Renderer::LoadSpriteFromData(newData, data.Width / 2, data.Height / 2);
				//free(data.Data);
				//free(newData);
			}
		}

		for (auto obj : Renderer::GetAllChunkObjectsInArea(m_position, m_scale))
		{
			const int spriteIndex = obj->GetSprite()->GetSpriteId();
			if (spriteIndex + m_spriteCountBeforePixelated >= Renderer::GetSpriteCount()) { continue; }

			obj->SetSpriteId(spriteIndex + m_spriteCountBeforePixelated);
		}
	}

	void GlitchedRegion::Update(GLFWwindow* window)
	{
		for (auto obj : Renderer::GetAllActiveObjectsInArea(m_position, m_scale))
		{
			if (obj->GetSprite() == nullptr)
			{
				continue;
			}

			const int spriteIndex = obj->GetSprite()->GetSpriteId();

			if (m_spriteCountBeforePixelated > spriteIndex)
			{
				obj->SetSprite(new Sprite(spriteIndex + m_spriteCountBeforePixelated));
			}

		}
	}

	void GlitchedRegion::Render(const Vec2& cameraPosition)
	{
#if DEBUG_RENDER_GLITCHED_AREAS
		GameObject::Render(cameraPosition);
#endif

		// Don't render this.
	}

}


