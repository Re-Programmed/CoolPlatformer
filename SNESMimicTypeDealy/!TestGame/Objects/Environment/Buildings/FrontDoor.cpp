#include "FrontDoor.h"
#include "../../../TestGame.h"
#include "../../../../Input/InputManager.h"
#include "../../../../Objects/Instantiate/LevelObjectHandler.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	FrontDoor::FrontDoor(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, std::string room)
		: GameObject(position, scale, sprite), m_room(room), m_enteredState{ Vec2::Zero, m_position, m_room }
	{
		
	}

	void FrontDoor::Update(GLFWwindow* window)
	{
		if (InputManager::GetKeyUpDown(PLAYER_MOVE_UP) & InputManager::KEY_STATE_PRESSED)
		{
			if (Vec2::Distance(TestGame::ThePlayer->GetPosition() + TestGame::ThePlayer->GetScale() / 2.f, m_position + m_scale / 2.f) < m_scale.X)
			{
				//Player is entering the door.
				
				if (m_room == "exit")
				{
					for (GameObject* content : m_roomContents)
					{
						Renderer::DestroyObject(content);
					}

					//Return to previous state.
					m_position = m_enteredState.DoorPosition;
					m_room = m_enteredState.DoorCode;
					TestGame::ThePlayer->SetPosition(m_enteredState.PlayerPosition);
					TestGame::INSTANCE->GetCamera()->SetPosition(m_enteredState.PlayerPosition);
					return;
				}

				std::vector<GameObject*> roomObjects = Instantiate::LevelObjectHandler::GetLevelObjects(m_room);

				for (GameObject* roomObject : roomObjects)
				{
					roomObject->SetPosition(roomObject->GetPosition());
				}

				m_enteredState = { TestGame::ThePlayer->GetPosition(), m_position, m_room };

				Vec2 pos{ 175, 175 };
				TestGame::ThePlayer->SetPosition(pos);
				TestGame::INSTANCE->GetCamera()->SetPosition(pos);

				m_roomContents = roomObjects;

				m_room = "exit";
				m_position = Vec2{ pos.X - m_scale.X / 2.f, pos.Y };
			}
		}
	}
}
