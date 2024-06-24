#pragma once

#include "../../../Objects/GameObject.h"

namespace GAME_NAME::Objects
{
	class BreakableBlock
		: public GameObject
	{
	public:
		BreakableBlock(Vec2 position, Vec2 scale, Rendering::Sprite* sprite = nullptr, double mineTime = 1.0, int mineResistance = 0);

		void Render(const Vec2& cameraPosition) override;

		void Update(GLFWwindow* window) override;
	private:
		/// <summary>
		/// True if the block is currently hovered for mining.
		/// </summary>
		bool m_isHovered = false;

		/// <summary>
		/// How long it takes to break this object.
		/// </summary>
		const double m_mineTime;
		/// <summary>
		/// The minimum tool strength required to break this object.
		/// </summary>
		const int m_mineResistance;

		/// <summary>
		/// Used to fade in and out the hover outline.
		/// </summary>
		static double m_hoverDisplayPercent;

		/// <summary>
		/// How long the user has been mining a block for.
		/// </summary>
		static double m_currentMiningTime;
	};
}