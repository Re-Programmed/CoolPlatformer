#include "Door.h"
#include "../../../TestGame.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	void Door::Update(GLFWwindow* window)
	{

		//Check if player is near door -- door should open.
		if (Vec2::Distance(TestGame::ThePlayer->GetPosition(), m_position) < m_doorOpenDistance)
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
		m_isOpen = true;
	}

	void Door::close()
	{
		if (!m_isOpen) { return; }
		flipSprite();
		m_isOpen = false;
	}

	void Door::flipSprite()
	{
		Rendering::Sprite* const temp = new Rendering::Sprite(*m_sprite);
		delete m_sprite;

		m_sprite = m_openSprite;
		m_openSprite = temp;
	}
}
