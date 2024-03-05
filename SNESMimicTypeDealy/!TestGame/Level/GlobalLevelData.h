#pragma once
#include <cstdint>
#include <string>

namespace GAME_NAME::Level
{
	/// <summary>
	/// Used to track data about the current level that will change based on actions throughout the level.
	/// </summary>
	class GlobalLevelData
	{
	public:

		GlobalLevelData(std::string levelPath);

		/// <summary>
		/// Updates the current amount of points the player(s) has/have gotten and all related graphical displays.
		/// </summary>
		/// <param name="pointChange">How much to increase/decrease the current points by.</param>
		void UpdatePoints(int16_t pointChange);

		inline uint16_t GetPoints() { return m_points; }

		/// <summary>
		/// Returns the relative file path to the current level's files.
		/// </summary>
		inline std::string GetLevelPath()
		{
			return m_levelPath;
		}

	private:
		/// <summary>
		/// The points gathered on the current level.
		/// </summary>
		uint16_t m_points = 0;

		/// <summary>
		/// The relative file path to the level that was loaded.
		/// </summary>
		const std::string m_levelPath;
	};
}