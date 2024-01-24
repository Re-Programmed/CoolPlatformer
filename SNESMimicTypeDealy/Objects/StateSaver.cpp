#include "StateSaver.h"
#include "../Resources/Save/SaveManager.h"

std::vector<GAME_NAME::Objects::GameObjectState*> GAME_NAME::Objects::StateSaver::m_toBeSaved;

void GAME_NAME::Objects::StateSaver::RegisterToBeSaved(GameObjectState* state)
{
	m_toBeSaved.push_back(state);
	state->SetToBeSaved(true);
}

void GAME_NAME::Objects::StateSaver::SaveStates()
{
	for (GameObjectState* gos : m_toBeSaved)
	{
		gos->SaveState();
		gos->SetToBeSaved(false);

		//delete gos;
	}

	m_toBeSaved.clear();
}
