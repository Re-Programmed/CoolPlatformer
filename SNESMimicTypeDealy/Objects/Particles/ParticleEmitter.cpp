#include "ParticleEmitter.h"
#include "../../Utils/Time/GameTime.h"

namespace GAME_NAME::Objects::Particles
{

	ParticleEmitter::ParticleEmitter(Vec2 position, float maxParticleLifetime)
		: GameObject(position, Vec2(0, 0), nullptr, 0.0F), m_maxParticleLifetime(maxParticleLifetime)
	{
		
	}

	void ParticleEmitter::Render(Vec2 cameraPosition)
	{
		//Render Particles

		for (int i = 0; i < m_spawned.size(); i++)
		{
			m_spawned[i].PSprite->Render(cameraPosition, m_spawned[i].Position, m_spawned[i].Scale, m_spawned[i].Rotation);
			m_spawned[i].Lifetime += Utils::Time::GameTime::GetScaledDeltaTime();

			if (m_spawned[i].Lifetime >= m_maxParticleLifetime)
			{
				m_spawned.erase(m_spawned.begin() + i);
				i--;
			}
		}
		
	}

	void ParticleEmitter::SpawnParticle()
	{
		Particle emit(m_particleCopy[std::rand() / (RAND_MAX / m_particleCopy.size())]);

		emit.Position += m_position;

		m_spawned.push_back(emit);
	}
}
