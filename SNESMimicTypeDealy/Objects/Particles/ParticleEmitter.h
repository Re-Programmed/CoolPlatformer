#pragma once
#include "../GameObject.h"
#include "../../Rendering/Sprite.h"
#include <vector>
#include <algorithm>
#include "../../Components/Physics/Collision/ActiveBoxCollider.h"


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

		float Gravity;

		float Opacity, TargetOpacity;

		Sprite* const PSprite;

		float Lifetime;

		Particle(Vec2 position, Vec2 scale, float rotation, Vec2 velocity, float rotationalVelocity, float opacity, Sprite* const sprite, float InitialLifetime = 0.f) : Position(position), Scale(scale), Rotation(rotation), Velocity(velocity),
			RotationalVelocity(rotationalVelocity), Opacity(opacity), PSprite(sprite), Lifetime(InitialLifetime), ConstantVelocity(0), TargetOpacity(opacity), TargetScale(scale), Gravity(0.f) {};

		Particle(GameObject* gameObject) : Position(gameObject->GetPosition()), Scale(gameObject->GetScale()), Rotation(gameObject->GetRotation()), Velocity(Vec2::Zero), RotationalVelocity(0.f), Opacity(1.f), PSprite(gameObject->GetSprite()),
			Lifetime(0.f), ConstantVelocity(0), TargetOpacity(1.f), TargetScale(Scale), Gravity(0.f) {};

		Particle(GameObject&& gameObject) : Position(gameObject.GetPosition()), Scale(gameObject.GetScale()), Rotation(gameObject.GetRotation()), Velocity(Vec2::Zero), RotationalVelocity(0.f), Opacity(1.f), PSprite(gameObject.GetSprite()),
			Lifetime(0.f), ConstantVelocity(0), TargetOpacity(1.f), TargetScale(Scale), Gravity(0.f)
		{	
		};

		Particle& operator=(const Particle& other)
		{
			Particle p(other.Position, other.Scale, other.Rotation, other.Velocity, other.RotationalVelocity, other.Opacity, other.PSprite, other.Lifetime);
			return *this;
		}
	};

	class ParticleEmitter 
		: public GameObject
	{
	public:
		ParticleEmitter(Vec2 position, float maxParticleLifetime = 5.f, bool allowCollision = false);

		void Render(const Vec2& cameraPosition) override;

		void SpawnParticle(Vec2 velocity = { 0, 0 }, float gravity = 0.f, float rotation = 0.f);

		inline void SpawnParticles(uint8_t numParticles, Vec2 maxVelocity = { 0, 0 }, float gravity = 0.f, float rotation = 0.f)
		{
			if (m_allowCollisions)
			{
				m_previousFrameColliders.rehash(numParticles);
			}


			for (uint8_t i = 0; i < numParticles; i++)
			{
				Vec2 velocity = { std::rand() * maxVelocity.X * 2 / RAND_MAX - maxVelocity.X, std::rand() * maxVelocity.Y / RAND_MAX };
				this->SpawnParticle(velocity, gravity, rotation);
			}
		}

		inline void SetAllowCollisions(bool allowCollisions) { m_allowCollisions = allowCollisions; }

		inline void RegisterParticle(Particle p)
		{
			m_particleCopy.push_back(p);
		}

		inline const size_t GetParticleCount()
		{
			return m_particleCopy.size();
		}

		void Update(GLFWwindow* window) override;
	private:
		float m_maxParticleLifetime;

		std::vector<Particle> m_particleCopy;

		std::vector<Particle> m_spawned;

		/// <summary>
		/// If true will add active box colliders to particles.
		/// </summary>
		bool m_allowCollisions;
		/// <summary>
		/// List of GameObjects that represent particles for collision.
		/// </summary>
		std::unordered_map<Components::Physics::Collision::ActiveBoxCollider*, Particle*> m_previousFrameColliders;

	};
}