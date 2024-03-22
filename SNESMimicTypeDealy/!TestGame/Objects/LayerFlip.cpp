#include "./LayerFlip.h"
#include "../TestGame.h"

namespace GAME_NAME::Objects
{
	void LayerFlip::Update(GLFWwindow* window, Objects::GameObject* object)
	{
		if (TestGame::INSTANCE->ThePlayer)
		{

		}
	}

	void LayerFlip::Init(Objects::GameObject* object)
	{
		m_upperLayer = new GameObject(object->GetPosition(), object->GetScale(), object->GetSprite(), object->GetRotation());
	}

	LayerFlip::~LayerFlip()
	{
		delete m_upperLayer;
	}
}