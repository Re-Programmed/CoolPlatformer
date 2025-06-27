#include "GlitchEffect.h"

#include "../../../../Rendering/DynamicSprite.h"
#include "../../../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME::Objects::Environment::Effects
{
	GlitchEffect::GlitchEffect(Vec2 position, Vec2 scale)
		: GameObject(position, scale, nullptr, 0.f)
	{
		for (int i = 0; i < 5; i++)
		{
			m_purples[i] = new GameObject(position + Vec2{ (float)std::rand() * 30.f / (float)RAND_MAX, (float)std::rand() * 30.f / (float)RAND_MAX } - Vec2{ 15.f, 15.f }, Vec2{ (float)std::rand() * 2.f / (float)RAND_MAX }, Renderer::GetSprite(SpriteBase(101)));
			Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_purples[i], false, 2, true));
		}
	}

	void GlitchEffect::Render(const Vec2& cameraPosition)
	{
		for (int i = 0; i < 5; i++)
		{
			m_purples[i]->Translate(Vec2{ std::sinf(2 * glfwGetTime() + i)/10.5f, std::cosf(glfwGetTime() + i) / 20.5f });
		}

		auto tSprite = Rendering::Renderer::GetDynamicSprite((std::rand() * RAND_TEXTURE_RANGE) / RAND_MAX);

		float r = (float)std::rand() / (float)RAND_MAX, g = (float)std::rand() / (float)RAND_MAX, b = (float)std::rand() / (float)RAND_MAX;

		r -= 0.25f;
		g -= 0.15f;
		b += 0.15f;

		const Vec4 PERC_75_VERTS[4] = {
		   { r, g, b, 0.75f},
		   { r, g, b, 0.75f },
		   { r, g, b, 0.75f },
		   { r, g, b, 0.75f }
		};

		tSprite->UpdateTextureColor(PERC_75_VERTS);

		tSprite->Render(cameraPosition, m_position, m_scale, m_rotation);
	}


}

