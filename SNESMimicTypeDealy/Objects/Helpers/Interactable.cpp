#include "Interactable.h"

#include "../../Utils/CollisionDetection.h"

namespace GAME_NAME::Objects
{
	Interactable::Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation, bool useBoundingBox)
		: GameObject(position, scale, sprite, rotation), m_interactionRadius(std::abs(scale.X) / 1.5), m_interactKey(interactKey), m_keyStateCheck(keyStateCheck), m_useBoundingBox(useBoundingBox)
	{

	}

	Interactable::Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, float interactionRadius, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation)
		: GameObject(position, scale, sprite, rotation), m_interactionRadius(interactionRadius), m_interactKey(interactKey), m_keyStateCheck(keyStateCheck), m_useBoundingBox(false)
	{

	}

	void Interactable::Update(GLFWwindow* window)
	{
		if (m_keyStateCheck & InputManager::KEY_STATE_NONE)
		{
			auto player = TestGame::ThePlayer;
			
			if (m_useBoundingBox)
			{
				if (CollisionDetection::BoxWithinBox(player->GetPosition(), player->GetScale(), m_position, m_scale))
				{
					onInteract(player, InputManager::GetKeyUpDown(m_interactKey));
				}

				return;
			}

			if (Vec2::Distance(player->GetPosition() + player->GetScale()/2.f, m_position + m_scale/2.f) < m_interactionRadius)
			{
				onInteract(player, InputManager::GetKeyUpDown(m_interactKey));
			}

			return;
		}else if (InputManager::GetKeyUpDown(m_interactKey) & m_keyStateCheck)
		{
			auto player = TestGame::ThePlayer;

			if (m_useBoundingBox)
			{
				if (CollisionDetection::BoxWithinBox(player->GetPosition(), player->GetScale(), m_position, m_scale))
				{
					onInteract(player, InputManager::GetKeyUpDown(m_interactKey));
				}

				return;
			}

			if (Vec2::Distance(player->GetPosition() + player->GetScale()/2.f, m_position + m_scale/2.f) < m_interactionRadius)
			{
				onInteract(player, m_keyStateCheck);
			}
		}

	}
}

