#include "FeralRabbit.h"

#include "../../../TestGame.h"

#define FERAL_RABBIT_AGRESSION_DISTANCE 64

namespace GAME_NAME::Objects::Enemies
{
	FeralRabbit::FeralRabbit(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, int jumpingSprite, PassiveRabbitAttributes* attributes)
		: PassiveRabbit(position, scale, sprite, jumpingSprite, attributes)
	{

	}

	void FeralRabbit::Update(GLFWwindow* window)
	{
		//Player is close, use attacking AI
		if (Vec2::Distance(m_position, TestGame::ThePlayer->GetPosition()) < FERAL_RABBIT_AGRESSION_DISTANCE)
		{
			m_allowPathfinding = true;
			setPathfinding(TestGame::ThePlayer->GetPosition());
			updateTextures(window);
			Enemy::Update(window);
			return;
		}

		PassiveRabbit::Update(window);
	}
}