#include "ExplosiveObject.h"

#include "../../TestGame.h"
#include "./Effects/Explosion.h"

#include "./Effects/BloodMark.h"

#define EXPLOSION_MARK_SPRITE SpriteBase(133)
#define EXPLOSION_MARK_SCALE Vec2{24,13.5f}

namespace GAME_NAME::Objects::Environment
{
	ExplosiveObject::ExplosiveObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float explosionRadius, float explosionPower, EXPLOSION_REASON sensitivity)
		: GameObject(position, scale, sprite), m_explosionPower(explosionPower), m_explosionRadius(explosionRadius), m_reason(sensitivity)
	{

	}

	void ExplosiveObject::Update(GLFWwindow* window)
	{
		if (m_reason & JUMPED_ON)
		{
			if (Vec2::Distance(TestGame::ThePlayer->GetPosition() + TestGame::ThePlayer->GetScale() / 2, m_position + m_scale / 2) < 1.f + m_scale.X / 2)
			{
				explode();
			}
		}
	}

	void ExplosiveObject::explode()
	{
using namespace Effects;

		Explosion* explosion = new Explosion(m_position + m_scale / 2, m_explosionRadius, m_explosionPower);
		Renderer::LoadActiveObject(explosion);

		Environment::BloodMark* floorMark = new Environment::BloodMark(this, m_position + Vec2(m_scale.X / 2.f, 0.f), Renderer::GetSprite(EXPLOSION_MARK_SPRITE), EXPLOSION_MARK_SCALE);
		Renderer::LoadObject(floorMark, 1);

		Renderer::DestroyObject(this);
	}
}

