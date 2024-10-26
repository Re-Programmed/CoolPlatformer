#include "ParticleEmitter.h"
#include "../../Utils/Time/GameTime.h"
#include "../../Rendering/DynamicSprite.h"

#include "../../Components/Physics/Collision/CollisionManager.h"

namespace GAME_NAME::Objects::Particles
{

	ParticleEmitter::ParticleEmitter(Vec2 position, float maxParticleLifetime, bool allowCollision)
		: GameObject(position, Vec2(0, 0), nullptr, 0.0F), m_maxParticleLifetime(maxParticleLifetime), m_allowCollisions(allowCollision)
	{
		
	}

	void ParticleEmitter::Render(const Vec2& cameraPosition)
	{
		//Render Particles

		for (int i = 0; i < m_spawned.size(); i++)
		{
			
			DynamicSprite particleSprite = DynamicSprite(m_spawned[i].PSprite->GetSpriteId());
			
			const Vec4 cols[4]{
				{ 1.f, 1.f, 1.f, m_spawned[i].Opacity },
				{ 1.f, 1.f, 1.f, m_spawned[i].Opacity },
				{ 1.f, 1.f, 1.f, m_spawned[i].Opacity },
				{ 1.f, 1.f, 1.f, m_spawned[i].Opacity }
			};

			particleSprite.UpdateTextureColor(cols);

			particleSprite.Render(cameraPosition, m_spawned[i].Position, m_spawned[i].Scale, m_spawned[i].Rotation);
		}
		
	}

	void ParticleEmitter::SpawnParticle(Vec2 velocity, float gravity, float rotation)
	{
		Particle emit(m_particleCopy[std::rand() / (RAND_MAX / m_particleCopy.size())]);

		emit.Position += m_position + Vec2(std::rand() * m_scale.X / RAND_MAX, std::rand() * m_scale.Y / RAND_MAX);
		emit.Velocity += velocity;
		emit.Gravity = gravity;
		//emit.Rotation = rotation;

		if (emit.ConstantVelocity.X != 0) {
			emit.ConstantVelocity.X += ((float)(std::rand()) / (float)RAND_MAX) * 1.75f - 0.375f;
		}

		if (emit.ConstantVelocity.Y != 0) {
			emit.ConstantVelocity.Y += ((float)(std::rand()) / (float)RAND_MAX) * 1.75f - 0.375f;
		}

		m_spawned.push_back(emit);
	}

	void ParticleEmitter::Update(GLFWwindow* window)
	{
using namespace GAME_NAME::Components::Physics::Collision;

		if (m_allowCollisions)
		{
			//Update each particle to their collided position.
			for (const auto& [collider, particle] : m_previousFrameColliders)
			{
				particle->Position = collider->GetObject()->GetPosition();
				delete collider->GetObject();
				delete collider;
			}

			m_previousFrameColliders.clear();
		}

		for (int i = 0; i < m_spawned.size(); i++)
		{
			//Update lifetime and add randomness to make particles despawn at different times.
			m_spawned[i].Lifetime += (float)Utils::Time::GameTime::GetScaledDeltaTime();


			if (m_spawned[i].Lifetime >= m_maxParticleLifetime)
			{
				m_spawned.erase(m_spawned.begin() + i);
				i--;

				continue;
			}

			//Update velocities.
			m_spawned[i].Position += m_spawned[i].Velocity + m_spawned[i].ConstantVelocity;
			m_spawned[i].Rotation += m_spawned[i].RotationalVelocity;

			//Update scale and opacity.
			m_spawned[i].Opacity = std::lerp(m_spawned[i].Opacity, m_spawned[i].TargetOpacity, 1.f / (m_maxParticleLifetime * 30.f));
			m_spawned[i].Scale.X = std::lerp(m_spawned[i].Scale.X, m_spawned[i].TargetScale.X, 1.f / (m_maxParticleLifetime * 30.f));
			m_spawned[i].Scale.Y = std::lerp(m_spawned[i].Scale.Y, m_spawned[i].TargetScale.Y, 1.f / (m_maxParticleLifetime * 30.f));

			//Add drag.
			if (m_spawned[i].Velocity.X >= 0.1f) { m_spawned[i].Velocity.X -= (float)std::rand() / (RAND_MAX * 100.f); }
			else if (m_spawned[i].Velocity.X <= -0.1f) { m_spawned[i].Velocity.X += (float)std::rand() / (RAND_MAX * 100.f); }
			else
			{
				m_spawned[i].Velocity.X = 0.f;
			}

			if (m_spawned[i].Velocity.Y > -2.f)
			{
				m_spawned[i].Velocity.Y -= m_spawned[i].Gravity;
			}

			if (m_spawned[i].RotationalVelocity >= 0.1f) { m_spawned[i].RotationalVelocity -= 0.1f; }
			else if (m_spawned[i].RotationalVelocity <= -0.1f) { m_spawned[i].RotationalVelocity += 0.1f; }
			else
			{
				m_spawned[i].RotationalVelocity = 0.f;
			}

			if (m_allowCollisions)
			{
				Particle& p = m_spawned[i];
				GameObject* particleRepresentation = new GameObject(p.Position, p.Scale, nullptr, p.Rotation);
				ActiveBoxCollider* abc = new ActiveBoxCollider(false);
				abc->Init(particleRepresentation);

				CollisionManager::RegisterActiveColliderToBuffer(abc);
				m_previousFrameColliders.insert(std::make_pair(abc, &p));
			}
		}
	}
}
