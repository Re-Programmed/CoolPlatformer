#include "MiscStateGroup.h"
#include "StateSaver.h"

namespace GAME_NAME
{
	MiscStateGroup::MiscStateGroup(std::string destination)
		: m_destination(destination)
	{
		Objects::StateSaver::RegisterToBeSaved(this);
	}

	void MiscStateGroup::assignState(MiscState* state)
	{
		m_states.push_back(state);
	}

	std::string MiscStateGroup::GetSaveString()
	{
		std::string returnVal("");

		for (int i = 0; i < m_states.size(); i++)
		{
			MiscState* state = m_states[i];

			//if (state == nullptr)
			//{
			//	m_states.erase(m_states.begin() + i);
			//	i--;
			//	continue;
			//}

			size_t paramSize;
			GAME_NAME::MiscState::SaveParam* params = state->Encode(paramSize);

			for (unsigned int i = 0; i < paramSize; i++)
			{
				returnVal += params->Key + "+" + params->Value + "+";
			}
		}

		return returnVal;
	}

}   