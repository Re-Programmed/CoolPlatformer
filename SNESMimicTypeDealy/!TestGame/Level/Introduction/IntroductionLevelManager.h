#pragma once
#include "../LevelSystem.h"
#include <array>
#include "../../../Components/ComponentObject.h"
#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

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
		double m_rubeTimer = 0.0, m_rubeSubTimer = 0.0;

		void createRube();

		void executeRube();

		Components::ComponentObject* m_rubeBed;
		GameObject* m_rubeClock;
		std::array<Components::ComponentObject*, 4> m_rubePulleys;
		std::array<GameObject*, 4> m_rubeRopes;
		GameObject* m_rubeRopeBoard;
		GameObject* m_rubeSlantedShelf;
		Components::ComponentObject* m_rubeBlueBook1;
		GameObject* m_rubeLever;
		GAME_NAME::Components::Physics::Collision::ActiveBoxCollisionGravityObject* m_rubeBall;
		Components::ComponentObject* m_smallBallLaunch;
		std::array<GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject*, 4> m_shelfColliders;

		//Used for detecting certain processess during the rube animation.
		bool ilm_rube_flag = false, ilm_rube_flag_2 = false;
		GAME_NAME::Components::Physics::Collision::ActiveBoxCollisionGravityObject* ilm_player_flying = nullptr;
	};
}