#include "AngryFarmer.h"

#include "../../../TestGame.h"

#define ANGRY_FARMER_X_AGRESSION_DISTANCE 150
#define ANGRY_FARMER_Y_AGRESSION_DISTANCE 20

#define ANGRY_FARMER_CHASE_SPEED_MULT 4.f

namespace GAME_NAME::Objects::Enemies
{
	void AngryFarmer::Update(GLFWwindow* window)
	{
		if (m_isAggrivated)
		{
			//Angry at the player, chase the player.

			setPathfinding({ TestGame::ThePlayer->GetPosition().X, m_position.Y });
			Enemy::Update(window);

			return;
		}

		if (std::abs(TestGame::ThePlayer->GetPosition().X - m_position.X) < ANGRY_FARMER_X_AGRESSION_DISTANCE && std::abs(TestGame::ThePlayer->GetPosition().Y - m_position.Y) < ANGRY_FARMER_Y_AGRESSION_DISTANCE)
		{
			m_isAggrivated = true;

			//Play aggro animation.

			//Increase speed.
			m_enemyAttributes->MovementSpeed = ANGRY_FARMER_CHASE_SPEED_MULT;
			m_enemyAttributes->TerminalMovementSpeed *= ANGRY_FARMER_CHASE_SPEED_MULT;
		}

		LeftRightEnemy::Update(window);
	}

	AngryFarmer::AngryFarmer(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 leftAnchor, Vec2 rightAnchor, AngryFarmerAttributes* attributes)
		: LeftRightEnemy(position, scale, sprite, leftAnchor, rightAnchor, attributes)
	{

	}
}
