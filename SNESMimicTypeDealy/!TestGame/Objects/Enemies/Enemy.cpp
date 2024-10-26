#include "./Enemy.h"

#include "../../../Utils/Time/GameTime.h"

#include "../../../Resources/Save/SaveManager.h"

namespace GAME_NAME::Objects::Enemies
{
	void Enemy::Update(GLFWwindow* window)
	{
		if (!m_allowPathfinding)
		{
			m_pathfindTimeout.Timer = 0.f;
			goto finish_pathfind;
		}

		//Ignore Y pathfind? Check X distance.
		if (m_enemyAttributes->IgnoreYPathfind && std::abs(m_position.X - m_pathfind.X) < PATHFINDING_PADDING)
		{
			m_pathfindTimeout.Timer = 0.f;
			goto finish_pathfind;
		}
		
		//distance SCOPE.
		{
			float distance = Vec2::Distance(m_position, m_pathfind); //Distance from destination.

			if (distance <= PATHFINDING_PADDING)
			{
				m_pathfindTimeout.Timer = 0.f;
				goto finish_pathfind;
			}

			//Check if pathfinding has been attempted and failed many times.
			if (std::abs(distance - m_pathfindTimeout.Distance) < PATHFINDING_PADDING)
			{
				m_pathfindTimeout.Timer += Utils::Time::GameTime::GetScaledDeltaTime();
			}
			else {
				m_pathfindTimeout.Timer = 0.f;
			}

			m_pathfindTimeout.Distance = distance;

			//Move the enemy towards the pathfinding point if they are not already at it and ensure the enemy dosent exceed terminal velocity.
			if (std::abs(m_physics->GetVelocity().X) < m_enemyAttributes->TerminalMovementSpeed)
			{
				m_physics->AddVelocity(Vec2((m_position.X - m_pathfind.X < 0) ? m_enemyAttributes->MovementSpeed : -m_enemyAttributes->MovementSpeed, 0));
			}
		}

finish_pathfind:
		ActiveBoxCollisionGravityObject::Update(window);
	}

	void Enemy::Damage(float damage)
	{
		m_health -= damage;
	}

	void Enemy::Heal(float health)
	{

	}

	void Enemy::Kill()
	{

	}

	void Enemy::LoadState()
	{
		std::string resultStr("");
		Resources::SaveManager::GetLevelString(resultStr, m_objectSaveID);

		
	}

	void Enemy::SaveState()
	{
		std::string saveStr = "";
		saveStr = saveStr + std::to_string(m_position.X) + ",";
		saveStr = saveStr + std::to_string(m_position.Y) + ",";
		saveStr = saveStr + std::to_string(m_health);

		Resources::SaveManager::SaveLevelString(saveStr, m_objectSaveID);
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