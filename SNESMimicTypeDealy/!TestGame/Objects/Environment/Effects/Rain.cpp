#include "Rain.h"

#include "../../../TestGame.h"

#define RAIN_PARTICLE_EMITTER_HEIGHT 130.f

#define RAIN_SPRITE SpriteBase(131)

namespace GAME_NAME::Objects::Environment::Effects
{
	ParticleEmitter* Rain::m_rainEffect = nullptr;
	Rain* Rain::m_loopInstance = nullptr;

	void Rain::StartRainEffect()
	{
		if (!m_rainEffect)
		{
			m_rainEffect = new ParticleEmitter(TestGame::ThePlayer->GetPosition() + Vec2{ -250.f, RAIN_PARTICLE_EMITTER_HEIGHT }, 25.f, false);
			Particle rainP(Vec2::Zero, { 1.5f, 3.25f }, 45.f, Vec2::MinusOneY, 0.f, 0.75f, Renderer::GetSprite(RAIN_SPRITE));
			rainP.ConstantVelocity = Vec2::OneX;
			m_rainEffect->RegisterParticle(rainP);
			

			Renderer::LoadActiveObject(m_rainEffect, 2);
		}

		m_rainEffect->SpawnParticlesLooping(0.25, 18, { 0.f, 0.f }, 1.5f, 45.f, { 300.f, 20.f });
	
		//Start update loop.
		if (!m_loopInstance)
		{
			m_loopInstance = new Rain();
		}
	}

	void Rain::Update(GLFWwindow* window)
	{
		if (!m_rainEffect) { return; }
		m_rainEffect->SetPosition(TestGame::ThePlayer->GetPosition() + Vec2{ -180.f, RAIN_PARTICLE_EMITTER_HEIGHT });
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
}