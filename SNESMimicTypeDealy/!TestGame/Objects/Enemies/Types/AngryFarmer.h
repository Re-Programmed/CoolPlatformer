#pragma once

#include "LeftRightEnemy.h"

namespace GAME_NAME::Objects::Enemies
{
	class AngryFarmer
		: public LeftRightEnemy
	{
	public:
		struct AngryFarmerAttributes
			: public LeftRightEnemyAttributes
		{
			AngryFarmerAttributes() = default;
		};

		void Update(GLFWwindow* window) override;

		AngryFarmer(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 leftAnchor, Vec2 rightAnchor, AngryFarmerAttributes* attributes = new AngryFarmerAttributes());

	private:
		/// <summary>
		/// True if the farmer has spotted the player in his vision. Causes the farmer to begin chasing the player.
		/// </summary>
		bool m_isAggrivated = false;
	};
}