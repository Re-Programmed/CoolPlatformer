#include "MiscStateGroup.h"

namespace GAME_NAME
{
	template<class T>
	MiscStateGroup<T>::MiscStateGroup(std::string destination)
		: m_destination(destination)
	{

	}

	template<class T>
	void MiscStateGroup<T>::registerMiscState(MiscState<T> state)
	{
		m_states.push_back(state);
	}

	template<class T>
	void MiscStateGroup<T>::saveStates()
	{
		//Write states to save destination
	}
}