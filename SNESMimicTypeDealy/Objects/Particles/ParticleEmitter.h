#pragma once
#include "../GameObject.h"
#include "../../Rendering/Sprite.h"
#include <vector>

namespace GAME_NAME::Objects::Particles
{
	using namespace Rendering;

	struct Particle
	{
		Vec2 Position;
		Vec2 Scale, TargetScale;
		float Rotation;

		Vec2 Velocity, ConstantVelocity;
		float RotationalVelocity;

		float Opacity, TargetOpacity;

		Sprite* const PSprite;

		float Lifetime;

		Particle(Vec2 position, Vec2 scale, float rotation, Vec2 velocity, float rotationalVelocity, float opacity, Sprite* const sprite, float InitialLifetime = 0.f) : Position(position), Scale(scale), Rotation(rotation), Velocity(velocity),
			RotationalVelocity(rotationalVelocity), Opacity(opacity), PSprite(sprite), Lifetime(InitialLifetime), ConstantVelocity(0), TargetOpacity(opacity), TargetScale(scale) {};

		Particle(GameObject* gameObject) : Position(gameObject->GetPosition()), Scale(gameObject->GetScale()), Rotation(gameObject->GetRotation()), Velocity(Vec2::Zero), RotationalVelocity(0.f), Opacity(1.f), PSprite(gameObject->GetSprite()),
			Lifetime(0.f), ConstantVelocity(0), TargetOpacity(1.f), TargetScale(Scale) {};

		Particle(GameObject&& gameObject) : Position(gameObject.GetPosition()), Scale(gameObject.GetScale()), Rotation(gameObject.GetRotation()), Velocity(Vec2::Zero), RotationalVelocity(0.f), Opacity(1.f), PSprite(gameObject.GetSprite()),
			Lifetime(0.f), ConstantVelocity(0), TargetOpacity(1.f), TargetScale(Scale)
		{	
		};

		Particle& operator=(const Particle& other)
		{
			Particle p(other.Position, other.Scale, other.Rotation, other.Velocity, other.RotationalVelocity, other.Opacity, other.PSprite, other.Lifetime);
			
			return p;
		}
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

		void Update(GLFWwindow* window) override;
	private:
		float m_maxParticleLifetime;

		std::vector<Particle> m_particleCopy;

		std::vector<Particle> m_spawned;
	};
}