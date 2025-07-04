#pragma once
#include "../LevelSystem.h"
#include <array>
#include "../../../Components/ComponentObject.h"

using namespace GAME_NAME::Objects;

namespace GAME_NAME::Level
{
	class IntroductionLevelManager
		: public LevelSystem
	{
	public:
		IntroductionLevelManager();

		void Update(GLFWwindow* window) override;

	private:
		void createRube();

		std::array<Components::ComponentObject*, 4> m_rubePulleys;
		std::array<GameObject*, 4> m_rubeRopes;
		GameObject* m_rubeRopeBoard;
		GameObject* m_rubeSlantedShelf;
		Components::ComponentObject* m_rubeBlueBook1;
		GameObject* m_rubeLever;
		GameObject* m_rubeBall;
	};
}