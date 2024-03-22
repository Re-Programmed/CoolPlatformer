#include "LeftRightEnemy.h"

namespace GAME_NAME::Objects::Enemies
{
	LeftRightEnemy::LeftRightEnemy(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 leftAnchor, Vec2 rightAnchor)
		: Enemy(position, scale, sprite), m_leftAnchor(leftAnchor), m_rightAnchor(rightAnchor), m_movingLeft(std::rand() < (RAND_MAX/2))
	{

	}

	void LeftRightEnemy::Update(GLFWwindow* window)
	{
		Enemy::Update(window);

		if(completedPathfinding())
		{
			m_movingLeft = !m_movingLeft;

			setPathfinding(m_movingLeft ? m_leftAnchor : m_rightAnchor);
		}
	}
}

