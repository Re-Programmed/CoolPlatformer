#include "Door.h"
#include "../../../TestGame.h"
#include "../../../../Utils/CollisionDetection.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	void Door::Update(GLFWwindow* window)
	{

		//Check if player is near door -- door should open.
		if (CollisionDetection::BoxWithinBox(TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale(), (m_isOpen ? m_position : Vec2{ m_position.X - 13, m_position.Y }) - m_doorOpenDistance / 2, m_isOpen ? (m_scale + m_doorOpenDistance) : (Vec2{ m_scale.X + 13, m_scale.Y } + m_doorOpenDistance)))
		{
			//Open door.
			open();

			return;
		}

		//Close the door.
		close();


		//Update collision if the door is currently closed.
		m_boxCollider->Update(window, this);
	}

	void Door::open()
	{
		if (m_isOpen) { return; }
		flipSprite();

		//Resize door.
		m_scale = { m_scale.X + 13, m_scale.Y };
		m_position = { m_position.X - 13, m_position.Y };

		m_isOpen = true;
	}

	void Door::close()
	{
		if (!m_isOpen) { return; }
		flipSprite();

		//Resize door.
		m_scale = { m_scale.X - 13, m_scale.Y };
		m_position = { m_position.X + 13, m_position.Y };

		m_isOpen = false;
	}

	void Door::flipSprite()
	{
		const std::shared_ptr<Rendering::Sprite> temp = std::make_shared<Sprite>(m_sprite->GetSpriteId());

		m_sprite = m_openSprite;
		m_openSprite = temp;
	}
}
