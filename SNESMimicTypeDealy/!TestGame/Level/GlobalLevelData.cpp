#include "GlobalLevelData.h"
#include "./LevelInfoDisplay.h"

namespace GAME_NAME::Level
{
	GlobalLevelData::GlobalLevelData(std::string levelPath)
		: m_levelPath(levelPath)
	{
		LevelInfoDisplay::UpdateDSP(0);
	}

	void GlobalLevelData::UpdatePoints(int16_t pointChange)
	{
		m_points += pointChange;

		//TODO: Update graphical display for points.
		LevelInfoDisplay::UpdateDSP(m_points);
	}


}
