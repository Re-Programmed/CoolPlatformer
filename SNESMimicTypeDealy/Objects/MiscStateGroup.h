#pragma once
#include <vector>
#include "MiscState.h"

namespace GAME_NAME
{
	template<class T>
	class MiscStateGroup
	{
	public:
		MiscStateGroup(std::string destination);
	protected:
		void registerMiscState(MiscState<T> state);

		void saveStates();
	private:
		std::vector<MiscState<T>> m_states;
		std::string m_destination;
	};

}