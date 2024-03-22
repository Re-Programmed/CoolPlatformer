#pragma once

#include "../Enemy.h"

namespace GAME_NAME::Objects::Enemies
{
	class LeftRightEnemy
		: public Enemy
	{
	public:
		LeftRightEnemy(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 leftAnchor, Vec2 rightAnchor);

		void Update(GLFWwindow* window) override;

	protected:
		bool m_movingLeft;
		Vec2 m_leftAnchor, m_rightAnchor;
	};
}