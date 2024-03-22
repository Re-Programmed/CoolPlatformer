#pragma once
#include <vector>
#include "MiscState.h"

namespace GAME_NAME
{
	class MiscStateGroup
	{
	public:
		MiscStateGroup(std::string destination);

		inline std::string GetName()
		{
			return m_destination;
		}

		std::string GetSaveString();
	protected:
		void assignState(MiscState* state);

		inline void clearStates()
		{
			for (MiscState* state : m_states)
			{
				delete state;
			}

			m_states.clear();
		}
	private:
		std::vector<MiscState*> m_states;
		std::string m_destination;
	};

}