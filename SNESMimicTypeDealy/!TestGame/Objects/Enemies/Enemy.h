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
		struct EnemyAttributes
		{
			float MovementSpeed = 5.0F;
			float TerminalMovementSpeed = 20.F;
			
			struct TempAttributes
			{
				float Gravity = 1.5F;
				float FrictionDrag = 4.F;
			};

			TempAttributes* InputAttributes;

			EnemyAttributes() = default;

			EnemyAttributes(const EnemyAttributes& enemyAttributes)
				: MovementSpeed(enemyAttributes.MovementSpeed), TerminalMovementSpeed(enemyAttributes.TerminalMovementSpeed), InputAttributes(enemyAttributes.InputAttributes)
			{}

			EnemyAttributes(EnemyAttributes&& enemyAttributes) noexcept
				: MovementSpeed(enemyAttributes.MovementSpeed), TerminalMovementSpeed(enemyAttributes.TerminalMovementSpeed), InputAttributes(enemyAttributes.InputAttributes)
			{}

			EnemyAttributes(float movementSpeed, float terminalMovementSpeed, TempAttributes* tempAttributes)
				: MovementSpeed(movementSpeed), TerminalMovementSpeed(terminalMovementSpeed), InputAttributes(tempAttributes)
			{}

			TempAttributes GetInputAttributes()
			{
				if (InputAttributes == nullptr)
				{
					return TempAttributes();
				}

				TempAttributes attribs = *InputAttributes;
				return attribs;
				delete InputAttributes;
			}

			~EnemyAttributes()
			{
				delete InputAttributes;
			}
		};

		Enemy(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, EnemyAttributes* attributes = new EnemyAttributes())
			: ActiveBoxCollisionGravityObject(position, scale, sprite), m_pathfind(position), m_enemyAttributes(attributes)
		{
			EnemyAttributes::TempAttributes startAttributes = attributes->GetInputAttributes();
			m_physics->SetGravityStrength(startAttributes.Gravity);
			m_physics->SetFrictionDrag(startAttributes.FrictionDrag);
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

		~Enemy();

		EnemyAttributes* m_enemyAttributes;
	private:
		Vec2 m_pathfind;
	};
}