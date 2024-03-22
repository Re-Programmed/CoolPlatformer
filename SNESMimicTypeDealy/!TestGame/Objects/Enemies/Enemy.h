#pragma once

#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"

constexpr uint8_t PATHFINDING_PADDING = 1;

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
			m_physics->SetGravityStrength(1.5F);
			m_physics->SetFrictionDrag(4.F);
		}

		void Update(GLFWwindow* window) override;
	protected:
		/// <summary>
		/// Returns true if the enemy has reached its destination.
		/// </summary>
		/// <returns></returns>
		inline bool completedPathfinding() { return Vec2::Distance(m_pathfind, m_position) <= PATHFINDING_PADDING; }

		inline void setPathfinding(Vec2 position)
		{
			this->m_pathfind = position;
		}
	private:
		Vec2 m_pathfind;
	};
}