#pragma once
#include "../GameObject.h"
#include "../../Rendering/Sprite.h"
#include <vector>

namespace GAME_NAME::Objects::Particles
{
	using namespace Rendering;

	typedef struct Particle
	{
		Vec2 Position;
		Vec2 Scale;
		float Rotation;

		Vec2 Velocity;
		float RotationalVelocity;

		float Opacity;

		Sprite* const PSprite;

		float Lifetime;

		Particle(Vec2 position, Vec2 scale, float rotation, Vec2 velocity, float rotationalVelocity, float opacity, Sprite* const sprite, float InitialLifetime = 0.f) : Position(position), Scale(scale), Rotation(rotation), Velocity(velocity),
			RotationalVelocity(rotationalVelocity), Opacity(opacity), PSprite(sprite), Lifetime(InitialLifetime) {};
	};

	class ParticleEmitter 
		: public GameObject
	{
	public:
		ParticleEmitter(Vec2 position, float maxParticleLifetime = 5.f);

		void Render(Vec2 cameraPosition) override;

		void SpawnParticle();

		inline void SpawnParticles(uint8_t numParticles)
		{
			for (uint8_t i = 0; i < numParticles; i++)
			{
				this->SpawnParticle();
			}
		}

		inline void RegisterParticle(Particle p)
		{
			m_particleCopy.push_back(p);
		}
	private:
		float m_maxParticleLifetime;

		std::vector<Particle> m_particleCopy;

		std::vector<Particle> m_spawned;
	};
}