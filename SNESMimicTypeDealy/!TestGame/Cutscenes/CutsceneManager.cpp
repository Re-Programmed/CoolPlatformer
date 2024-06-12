#include "CutsceneManager.h"
#include "../TestGame.h"

namespace GAME_NAME::Cutscenes
{
	std::vector<std::shared_ptr<Cutscene>> CutsceneManager::m_cutsceneQueue;

	void CutsceneManager::RegisterCutscene(std::shared_ptr<Cutscene> scene)
	{
		m_cutsceneQueue.push_back(scene);
	}

	void CutsceneManager::UpdateCutsceneTriggers()
	{
		if (m_cutsceneQueue.empty()) { return; }

		//Get the topmost cutscene and check if the player is within any of them.

		std::shared_ptr<Cutscene> &scene = m_cutsceneQueue[0];
		if (scene->IsWithin(GAME_NAME::TestGame::ThePlayer->GetPosition()))
		{
			if (scene->Trigger())
			{
				m_cutsceneQueue.erase(m_cutsceneQueue.begin());
			}
		}
	}
}
