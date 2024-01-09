#pragma once
#include <cstdint>

namespace GAME_NAME::Level
{
	/// <summary>
	/// Used to track data about the current level that will change based on actions throughout the level.
	/// </summary>
	class GlobalLevelData
	{
	public:
		/// <summary>
		/// Updates the current amount of points the player(s) has/have gotten and all related graphical displays.
		/// </summary>
		/// <param name="pointChange">How much to increase/decrease the current points by.</param>
		void UpdatePoints(int64_t pointChange);
	private:
		/// <summary>
		/// The points gathered on the current level.
		/// </summary>
		uint64_t m_points;
	};
}