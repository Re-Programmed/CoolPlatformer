#include "Rain.h"

#include "../../../TestGame.h"

#define RAIN_PARTICLE_EMITTER_HEIGHT 110.f

#define RAIN_SPRITE SpriteBase(131)

namespace GAME_NAME::Objects::Environment::Effects
{
	ParticleEmitter* Rain::m_rainEffect = nullptr;
	Rain* Rain::m_loopInstance = nullptr;

	void Rain::StartRainEffect()
	{
		if (!m_rainEffect)
		{
			m_rainEffect = new ParticleEmitter(0.f, -1.f, true);
		
			m_rainEffect->SetScale(100.f); //Set scale to prevent the rain from disabling its rendering due to being offscreen.

			m_rainEffect->SetOnParticleCollision(OnRainParticleCollision);

			Particle rainP({-100.f /*To adjust for padding added to make rain work when running.*/, 0.f}, {1.5f, 3.25f}, 45.f, Vec2::MinusOneY, 0.f, 0.75f, Renderer::GetSprite(RAIN_SPRITE));
			rainP.TargetOpacity = 0;
			rainP.ConstantVelocity = Vec2::OneX;
			m_rainEffect->RegisterParticle(rainP);
			

			Renderer::LoadActiveObject(m_rainEffect, 2);
		}

		m_rainEffect->SpawnParticlesLooping(0.25, 40, { 0.f, 0.f }, 1.5f, 45.f, { 560.f, 20.f });
	
		//Start update loop.
		if (!m_loopInstance)
		{
			m_loopInstance = new Rain();
		}
	}

	void Rain::Update(GLFWwindow* window)
	{
		if (!m_rainEffect) { return; }

		Vec2 camCenter = Vec2{ TestGame::INSTANCE->GetCamera()->GetPosition().X + 160.f, TestGame::INSTANCE->GetCamera()->GetPosition().Y + 90.f };
		
		m_rainEffect->SetPosition(camCenter + Vec2{ -245.f, RAIN_PARTICLE_EMITTER_HEIGHT });
	}

	void Rain::EndRainEffect(bool freeSpawner)
	{
		if (m_loopInstance) 
		{
			delete m_loopInstance;
		}

		if (!m_rainEffect) { return; }

		m_rainEffect->StopLooping();

		if (freeSpawner)
		{
			Renderer::DestroyActiveObjectImmediate(m_rainEffect);
			delete m_rainEffect;
		}
	}

	void Rain::OnRainParticleCollision(Particle& particle)
	{
		particle.Lifetime = -1.f;
	}
}