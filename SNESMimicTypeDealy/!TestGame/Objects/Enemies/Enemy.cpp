#include "./Enemy.h"

namespace GAME_NAME::Objects::Enemies
{
	void Enemy::Update(GLFWwindow* window)
	{
		//Move the enemy towards the pathfinding point if they are not already at it.
		if (Vec2::Distance(m_position, m_pathfind) > PATHFINDING_PADDING && std::abs(m_physics->GetVelocity().X) < m_enemyAttributes->TerminalMovementSpeed)
		{
			m_physics->AddVelocity(Vec2((m_position.X - m_pathfind.X < 0) ? m_enemyAttributes->MovementSpeed : -m_enemyAttributes->MovementSpeed, 0));
		}

		ActiveBoxCollisionGravityObject::Update(window);
	}

	Enemy::~Enemy()
	{
		delete m_enemyAttributes;

		ActiveBoxCollisionGravityObject::~ActiveBoxCollisionGravityObject();
	}

	Enemy::EnemyAttributes::EnemyAttributes()
		: InputAttributes(nullptr)
	{

	}
}