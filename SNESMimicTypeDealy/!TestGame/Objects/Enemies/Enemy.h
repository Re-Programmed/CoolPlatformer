#pragma once

#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"

namespace GAME_NAME::Objects::Enemies
{
	using namespace Components::Physics::Collision;

	class Enemy
		: public ActiveBoxCollisionGravityObject
	{
	public:
		Enemy(Vec2 position, Vec2 scale, Rendering::Sprite* sprite)
			: ActiveBoxCollisionGravityObject(position, scale, sprite), m_pathfind(position)
		{
			m_physics->SetGravityStrength(4.5F);
		}

		void Update(GLFWwindow* window) override;
	protected:
		inline void setPathfinding(Vec2 position)
		{
			this->m_pathfind = position;
		}
	private:
		Vec2 m_pathfind;
	};
}