#include "FeralRabbit.h"

#include "../../../TestGame.h"

#define FERAL_RABBIT_AGRESSION_DISTANCE 200
#define FERAL_RABBIT_AWAKEN_DISTANCE 100
#define FERAL_RABBIT_AGRESSION_SPEED 20.f
#define FERAL_RABBIT_DEFAULT_SPEED 5.f

namespace GAME_NAME::Objects::Enemies
{
	FeralRabbit::FeralRabbit(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, int jumpingSprite, PassiveRabbitAttributes* attributes, bool beginSleeping)
		: PassiveRabbit(position, scale, sprite, jumpingSprite, attributes), m_isAsleep(beginSleeping)
	{

	}

	void FeralRabbit::Update(GLFWwindow* window)
	{
		if (m_isAsleep)
		{
			delete m_sprite;
			m_sprite = Renderer::GetSprite(95);

			if (Vec2::Distance(m_position, TestGame::ThePlayer->GetPosition()) < FERAL_RABBIT_AWAKEN_DISTANCE)
			{
				m_isAsleep = false;
			}

			return;
		}

		//Player is close, use attacking AI
		if (Vec2::Distance(m_position, TestGame::ThePlayer->GetPosition()) < FERAL_RABBIT_AGRESSION_DISTANCE)
		{
			m_enemyAttributes->MovementSpeed = FERAL_RABBIT_AGRESSION_SPEED;
			m_allowPathfinding = true;
			setPathfinding(TestGame::ThePlayer->GetPosition());
			updateTextures(window);
			Enemy::Update(window);
			return;
		}
		else {
			m_enemyAttributes->MovementSpeed = FERAL_RABBIT_DEFAULT_SPEED;
		}

		PassiveRabbit::Update(window);
	}
}