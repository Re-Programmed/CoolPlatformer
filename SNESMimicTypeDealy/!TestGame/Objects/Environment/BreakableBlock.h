#pragma once

#include "../../../Objects/GameObject.h"

namespace GAME_NAME::Objects
{
	class BreakableBlock
		: public GameObject
	{
	public:
		BreakableBlock(Vec2 position, Vec2 scale, Rendering::Sprite* sprite = nullptr);

		void Render(const Vec2& cameraPosition) override;

		void Update(GLFWwindow* window) override;
	private:
		/// <summary>
		/// True if the block is currently hovered for mining.
		/// </summary>
		bool m_isHovered = false;

		/// <summary>
		/// Used to fade in and out the hover outline.
		/// </summary>
		static double m_hoverDisplayPercent;
	};
}