#pragma once

#include "../Enemy.h"

namespace GAME_NAME::Objects::Enemies
{
	/// <summary>
	/// An enemy that moves left and right between two given points.
	/// </summary>
	class LeftRightEnemy
		: public Enemy
	{
	public:
		struct LeftRightEnemyAttributes
			: public EnemyAttributes
		{
			float EndpointPause = 1.F;

			LeftRightEnemyAttributes() = default;
		};

		/// <summary>
		/// Creates an enemy that will spawn with position, scale, and sprite. The enemy will then move between leftAnchor and rightAnchor. (A negative y position on the anchors will ignore the Y position of the enemy.)
		/// </summary>
		/// <param name="position">Where the enemy will spawn. (Should be between or at an anchor.)</param>
		/// <param name="scale">The scale of the enemy.</param>
		/// <param name="sprite">The sprite to use for the enemy.</param>
		/// <param name="leftAnchor">The left bound of movement for the enemy.</param>
		/// <param name="rightAnchor">The right bound of movement for the enemy.</param>
		LeftRightEnemy(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 leftAnchor, Vec2 rightAnchor, LeftRightEnemyAttributes* attributes = new LeftRightEnemyAttributes());

		~LeftRightEnemy();

#if _DEBUG
		//Debug render to show endpoints when the player is in debug mode.
		void Render(const Vec2& cameraPosition) override;
#endif

		void Update(GLFWwindow* window) override;

	protected:
		/// <summary>
		/// True if the enemy is currently moving toward the left anchor point.
		/// </summary>
		bool m_movingLeft;
		/// <summary>
		/// Anchor points for the enemy moving.
		/// </summary>
		Vec2 m_leftAnchor, m_rightAnchor;

	private:
		float m_pauseTimeCounter = 0.F;
	};
}