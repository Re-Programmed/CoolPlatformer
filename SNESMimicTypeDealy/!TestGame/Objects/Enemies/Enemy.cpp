#include "./Enemy.h"

constexpr float ENEMY_SPEED = 5.0f;
constexpr float TERMINAL_ENEMY_SPEED = 20.f;

namespace GAME_NAME::Objects::Enemies
{
	void Enemy::Update(GLFWwindow* window)
	{
		//Move the enemy towards the pathfinding point if they are not already at it.
		if (Vec2::Distance(m_position, m_pathfind) > PATHFINDING_PADDING && std::abs(m_physics->GetVelocity().X) < TERMINAL_ENEMY_SPEED)
		{
			m_physics->AddVelocity(Vec2((m_position.X - m_pathfind.X < 0) ? ENEMY_SPEED : -ENEMY_SPEED, 0));
		}

		ActiveBoxCollisionGravityObject::Update(window);
	}
}