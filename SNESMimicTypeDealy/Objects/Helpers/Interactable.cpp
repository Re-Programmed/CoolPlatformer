#include "Interactable.h"

namespace GAME_NAME::Objects
{
	Interactable::Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation)
		: GameObject(position, scale, sprite, rotation), m_interactionRadius(scale.X / 2), m_interactKey(interactKey), m_keyStateCheck(keyStateCheck)
	{

	}

	Interactable::Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, float interactionRadius, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation)
		: GameObject(position, scale, sprite, rotation), m_interactionRadius(interactionRadius), m_interactKey(interactKey), m_keyStateCheck(keyStateCheck)
	{

	}

	void Interactable::Update(GLFWwindow* window)
	{
		if (m_keyStateCheck & InputManager::KEY_STATE_NONE)
		{
			auto player = TestGame::ThePlayer;
			if (Vec2::Distance(player->GetPosition() + player->GetScale()/2.f, m_position + m_scale/2.f) < m_interactionRadius)
			{
				onInteract(player, InputManager::GetKeyUpDown(m_interactKey));
			}

			return;
		}else if (InputManager::GetKeyUpDown(m_interactKey) & m_keyStateCheck)
		{
			auto player = TestGame::ThePlayer;
			if (Vec2::Distance(player->GetPosition() + player->GetScale()/2.f, m_position + m_scale/2.f) < m_interactionRadius)
			{
				onInteract(player, m_keyStateCheck);
			}
		}

	}
}

