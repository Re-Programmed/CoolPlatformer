#include "BloodMark.h"
#include <algorithm> 


namespace GAME_NAME::Objects::Environment
{
	//Sprite possibilities.
	constexpr unsigned int BloodSpriteOptionsLength = 1;
	constexpr unsigned int BloodSpriteOptions[] = {
		SpriteBase(108)
	};

	const Vec2 BloodSpriteSizes[] = {
		{ 32.f / 1.5f, -12.f / 1.5f }
	};

	BloodMark::BloodMark(GameObject* spawnObject, Vec2 midpoint)
		: GameObject(midpoint, 0, nullptr, 0)
	{
		//Choose a random texture.
		unsigned int spriteIndex = std::rand() * BloodSpriteOptionsLength / RAND_MAX;

		m_scale = BloodSpriteSizes[spriteIndex];

		//Align sprite to top center of midpoint.
		m_position -= Vec2(m_scale.X / 2.f, 0);

		Vec2 pos = spawnObject->GetPosition();
		Vec2 scale = spawnObject->GetScale();

		//const float percXM = std::clamp(1.0f - (((m_position.X + m_scale.X) - pos.X) / m_scale.X), 0.0f, 1.0f);
		//const float percXG = std::clamp((((pos.X + scale.X) - m_position.X) / m_scale.X), 0.0f, 1.0f);

		//const float percYM = std::clamp(1.0f - ((pos.Y + scale.Y) - m_position.Y) / m_scale.Y, 0.0f, 1.0f);
		//const float percYG = std::clamp(1.0f - (((pos.Y + 2 * scale.Y) - m_position.Y) / m_scale.Y), 0.0f, 1.0f);


		//Ensure blood dosent extend off of object.
		/*Vec2 vertices[4]{
			Vec2(percXM, 0.f),
			Vec2(percXM, 1.f),
			Vec2(percXG, 1.f),
			Vec2(percXG, 0.f)
		};*/

		Sprite* sprite = Renderer::GetSprite(BloodSpriteOptions[spriteIndex]);
		m_sprite = new DynamicSprite(sprite->GetSpriteId()/*, vertices, vertices*/);
		delete sprite;
	}
}