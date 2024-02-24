#pragma once
#include "../../Objects/GUI/StaticGUIElement.h"

namespace GAME_NAME::Level
{
	
	using namespace Objects;

	class LevelInfoDisplay
	{
	public:
		static void UpdateDSP(uint16_t points);
	private:
		static std::unique_ptr<GUI::StaticGUIElement> m_pointsObjects[6];
	};
}