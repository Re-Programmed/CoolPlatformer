#pragma once

#include <vector>
#include "./GameObjectState.h"
#include <memory>


namespace GAME_NAME::Objects
{
	class StateSaver
	{
	public:
		static void RegisterToBeSaved(GameObjectState* state);

		static void SaveStates();
	private:
		static std::vector<GameObjectState*> m_toBeSaved;

	};
}