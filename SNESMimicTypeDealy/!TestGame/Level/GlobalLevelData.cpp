#include "GlobalLevelData.h"

namespace GAME_NAME::Level
{
	void GlobalLevelData::UpdatePoints(int64_t pointChange)
	{
		m_points += pointChange;

		//TODO: Update graphical display for points.
	}
}
