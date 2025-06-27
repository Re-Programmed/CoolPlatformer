#include "ExplosiveObject.h"

#include "../../TestGame.h"
#include "./Effects/Explosion.h"

#include "../../../Resources/Save/SaveManager.h"

#include "./Effects/BloodMark.h"


#define EXPLOSION_MARK_SPRITE SpriteBase(133)
#define EXPLOSION_MARK_SCALE Vec2{24,13.5f}

namespace GAME_NAME::Objects::Environment
{
	void ExplosiveObject::LoadState()
	{
		std::string result("f");
		Resources::SaveManager::GetLevelString(result, m_objectSaveID);

		if (result != "f")
		{
			Explode(false);
		}
	}

	void ExplosiveObject::SaveState()
	{
		Resources::SaveManager::SaveLevelString(std::string("" + SAVE_MNG_TRUE_STATE), m_objectSaveID);
		Renderer::DestroyObject(this);
	}

	ExplosiveObject::ExplosiveObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float explosionRadius, float explosionPower, EXPLOSION_REASON sensitivity, size_t saveID)
		: GameObject(position, scale, sprite), GameObjectState(saveID), m_explosionPower(explosionPower), m_explosionRadius(explosionRadius), m_reason(sensitivity)
	{
		LoadState();
	}

	void ExplosiveObject::Update(GLFWwindow* window)
	{
		if (TestGame::ThePlayer == nullptr) { return; }

		if (m_reason & JUMPED_ON)
		{
			if (Vec2::Distance(TestGame::ThePlayer->GetPosition() + TestGame::ThePlayer->GetScale() / 2, m_position + m_scale / 2) < 1.f + m_scale.X / 2)
			{
				Explode();
			}
		}
	}

	void ExplosiveObject::Explode(bool createExplosion)
	{
using namespace Effects;

		if (createExplosion)
		{
			Explosion* explosion = new Explosion(m_position + m_scale / 2, m_explosionRadius, m_explosionPower);
			Renderer::LoadActiveObject(explosion);
		}

		Environment::BloodMark* floorMark = new Environment::BloodMark(this, m_position + Vec2(m_scale.X / 2.f, 0.f), Renderer::GetSprite(EXPLOSION_MARK_SPRITE), EXPLOSION_MARK_SCALE);
		Renderer::LoadObject(floorMark, 1);

		if (createExplosion)
		{
			SaveState();
			m_scale = Vec2::Zero;
		}
		else {
			Renderer::DestroyObject(this);
		}

	}
}

