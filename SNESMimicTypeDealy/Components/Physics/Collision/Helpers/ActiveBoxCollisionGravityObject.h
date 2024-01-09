#pragma once

#include "../ActiveBoxCollider.h"
#include "../CollisionManager.h"
#include "../../GravityComponent.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				using namespace MathUtils;



				class ActiveBoxCollisionGravityObject	//An object that has a box collider, and is affected by gravity.
					: public Objects::GameObject
				{
				public:

					ActiveBoxCollisionGravityObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite)
						: GameObject(position, scale, sprite), m_boxCollider(new ActiveBoxCollider()), m_physics(new GravityComponent())
					{
						m_boxCollider->Init(this);
						m_physics->Init(this);
						m_boxCollider->SetOnCollision(onCollision);
						m_boxCollider->SetBeforeUpdate(beforeUpdate);
					}

					~ActiveBoxCollisionGravityObject()
					{
						//delete m_boxCollider;
						//delete m_physics;
					}

					bool GetActive()
					{
						return true;
					}
					
					void Update(GLFWwindow* window)
					{
						CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
					}

					void SetGravity(const float gVelocity)
					{
						m_physics->SetGravitationalVelocity(gVelocity);
					}

				protected:
					ActiveBoxCollider* const m_boxCollider;
					GravityComponent* const m_physics;			//Used for gravity and velocity.

					static void onCollision(Vec2 push, Objects::GameObject* obj)
					{
						ActiveBoxCollisionGravityObject* acgo = ((ActiveBoxCollisionGravityObject*)obj);
						acgo->onCollision(push);
						if (push.Y > 0) { acgo->SetGravity(0.f); }		//Resets the gravity to 0.
						else if (push.X != 0) { acgo->m_physics->SetVelocityX(0.f); }	//If you hit the side of an object, set the X velocity to 0.
					}

					/// <summary>
					/// Override to run code on collision.
					/// </summary>
					/// <param name="push">The direction the object is getting pushed to process the collision.</param>
					virtual void onCollision(Vec2 push)
					{

					}

					/// <summary>
					/// Called before collision checks.
					/// </summary>
					virtual void beforeCollision()
					{

					}

					//Ensures to update the physics before updating the collisions.
					static void beforeUpdate(Objects::GameObject* obj)
					{
						ActiveBoxCollisionGravityObject* acgo = ((ActiveBoxCollisionGravityObject*)obj);
						acgo->beforeCollision();
						acgo->m_physics->Update(nullptr, obj);
					}
				};

			}
		}
	}
}