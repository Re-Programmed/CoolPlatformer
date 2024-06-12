#pragma once
#include "Cutscene.h"
#include <memory>
#include <vector>

namespace GAME_NAME::Cutscenes
{
	class CutsceneManager
	{
	public:
		/// <summary>
		/// Registers a cutscene as a valid triggerable object.
		/// (Cutscenes become unregistered when triggered)
		/// </summary>
		/// <param name="scene">A shared pointer to the cutscene to register.</param>
		static void RegisterCutscene(std::shared_ptr<Cutscene> scene);

		static void UpdateCutsceneTriggers();
	private:
		static std::vector<std::shared_ptr<Cutscene>> m_cutsceneQueue;
	};
}