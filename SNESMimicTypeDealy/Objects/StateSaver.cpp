#include "StateSaver.h"
#include "../Resources/Save/SaveManager.h"
#include "../!TestGame/TestGame.h"

std::vector<GameObjectState*> GAME_NAME::Objects::StateSaver::m_toBeSaved;

void GAME_NAME::Objects::StateSaver::RegisterToBeSaved(GameObjectState* state)
{
	m_toBeSaved.push_back(state);
	state->SetToBeSaved(true);
}

void GAME_NAME::Objects::StateSaver::SaveStates()
{
	size_t len = Resources::SaveManager::GetCurrentFile().length();
	Resources::SaveManager::SetCurrentFile(Resources::SaveManager::GetCurrentFile() + TestGame::INSTANCE->GetGlobalLevelData()->GetLevelPath());

	for (GameObjectState* gos : m_toBeSaved)
	{
		gos->SaveState();
		gos->SetToBeSaved(false);

		delete gos;
	}

	Resources::SaveManager::SetCurrentFile(Resources::SaveManager::GetCurrentFile().substr(0, len));

	m_toBeSaved.clear();
}
