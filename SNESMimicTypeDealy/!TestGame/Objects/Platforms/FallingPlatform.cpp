#include "FallingPlatform.h"

#include "../../TestGame.h"
#include "../../../Utils/Time/GameTime.h"

constexpr float FALLING_PLATFORM_ACCELERATION = 0.01f;

namespace GAME_NAME::Objects::Platforms
{
	FallingPlatform::FallingPlatform(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float fallDelay)
		: StaticBoxCollisionObject(position, scale, sprite), m_fallDelay(fallDelay), m_storedInitY(position.Y)
	{
		SetOnCollision(onCollision);
	}

	bool FallingPlatform::onCollision(Vec2 push, Objects::GameObject* object, Objects::GameObject* collider)
	{
		//Landed on top.
		if (push.Y > 0)
		{
			//Increment gravity.
			FallingPlatform* fp = static_cast<FallingPlatform*>(object);
			fp->m_fallCounter += 0.001f;

			return fp->m_fallCounter < fp->m_fallDelay;
		}

		//Collision was not from top, ignore.
		return false;
	}

	void FallingPlatform::Update(GLFWwindow* window)
	{
		StaticBoxCollisionObject::Update(window);

		//Update gravity or the fall counter.
		if (m_fallCounter >= m_fallDelay)
		{
			if (m_position.Y < -m_scale.Y)
			{
				if (Vec2::Distance(TestGame::ThePlayer->GetPosition(), m_position) > 275.f)
				{
					m_gravity = 0;
					m_fallCounter = 0;
					m_position.Y = m_storedInitY;
				}
			}
			else {
				m_position.Y -= m_gravity;
				m_gravity += FALLING_PLATFORM_ACCELERATION;
			}
		}
		else if (m_fallCounter > 0)
		{
			m_fallCounter += (float)Utils::Time::GameTime::GetScaledDeltaTime();
		}
	}
}