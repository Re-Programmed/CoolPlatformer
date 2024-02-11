#include "Climbable.h"
#include "../../TestGame.h"
#include "../../../Input/InputManager.h"
#include "../../../Utils/CollisionDetection.h"

#define INPUT_CLIMB_KEY (InputManager::GetKeyUpDown(PLAYER_MOVE_UP) & InputManager::KEY_STATE_PRESSED)

namespace GAME_NAME::Objects::Util
{
	void Climbable::Update(GLFWwindow* window, Objects::GameObject* object)
	{
		if (INPUT_CLIMB_KEY)
		{
			if (Utils::CollisionDetection::BoxWithinBox(object->GetPosition(), object->GetScale(), TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale()))
			{
				//Set player climbing = !climbing.
			}
		}
	}

	void Climbable::Init(Objects::GameObject* object)
	{

	}
}