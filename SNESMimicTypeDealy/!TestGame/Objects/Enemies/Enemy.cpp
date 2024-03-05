#include "./Enemy.h"

namespace GAME_NAME::Objects::Enemies
{
	void Enemy::Update(GLFWwindow* window)
	{
		ActiveBoxCollisionGravityObject::Update(window);
	}
}