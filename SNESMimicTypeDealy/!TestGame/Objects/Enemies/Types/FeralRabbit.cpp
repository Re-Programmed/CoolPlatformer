#include "FeralRabbit.h"

#include "../../../TestGame.h"
#include "../../../../Utils/Time/GameTime.h"

/*
	--- FERAL RABBIT ATTRIBUTES ---
*/
#define FERAL_RABBIT_AGRESSION_DISTANCE 200
#define FERAL_RABBIT_AWAKEN_DISTANCE 50
#define FERAL_RABBIT_ATTACK_DISTANCE 20

#define FERAL_RABBIT_BASE_ATTACK_DAMAGE 5
#define FERAL_RABBIT_BASE_ATTACK_DELAY 2.0f

#define FERAL_RABBIT_AGRESSION_SPEED 20.f
#define FERAL_RABBIT_DEFAULT_SPEED 5.f

namespace GAME_NAME::Objects::Enemies
{
	FeralRabbit::FeralRabbit(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, int jumpingSprite, PassiveRabbitAttributes* attributes, bool beginSleeping, size_t saveID)
		: PassiveRabbit(position, scale, sprite, jumpingSprite, attributes, saveID), m_isAsleep(beginSleeping)
	{

	}

	void FeralRabbit::Update(GLFWwindow* window)
	{
		if (m_isDead) 
		{		
			PassiveRabbit::Update(window);
			return;
		}

		if (m_actionTimer > 0.f)
		{
			m_actionTimer -= Utils::Time::GameTime::GetScaledDeltaTime();
		}

		float distanceToPlayer = Vec2::Distance(m_position, TestGame::ThePlayer->GetPosition());

		if (m_isAsleep)
		{
			//delete m_sprite; //Cannot delete original sprite since it is used by PassiveRabbit as m_baseSprite.
			m_sprite.reset(Renderer::GetSprite(95));
			
			if (distanceToPlayer < FERAL_RABBIT_AWAKEN_DISTANCE)
			{
				m_isAsleep = false;
			}

			return;
		}

		//Player is close, use attacking AI
		if (distanceToPlayer < FERAL_RABBIT_AGRESSION_DISTANCE && m_actionTimer <= 0.f)
		{
			m_enemyAttributes->MovementSpeed = FERAL_RABBIT_AGRESSION_SPEED;
			m_allowPathfinding = true;
			setPathfinding(TestGame::ThePlayer->GetPosition());
			updateTextures(window);
			Enemy::Update(window);

			if (distanceToPlayer < FERAL_RABBIT_ATTACK_DISTANCE)
			{
				//Damage player since rabbit is in range.
				//TODO: Add slashing animation.
				TestGame::ThePlayer->Damage(FERAL_RABBIT_BASE_ATTACK_DAMAGE, nullptr);
				m_actionTimer = FERAL_RABBIT_BASE_ATTACK_DELAY;
			}

			return;
		}
		else {
			m_enemyAttributes->MovementSpeed = FERAL_RABBIT_DEFAULT_SPEED;
		}

		PassiveRabbit::Update(window);
	}
}