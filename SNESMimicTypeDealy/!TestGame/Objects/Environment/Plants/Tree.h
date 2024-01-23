#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Objects/GameObjectState.h"

namespace GAME_NAME::Objects::Environment::Plants
{
	class Tree : public GameObject, public GameObjectState
	{
	public:
		Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite = nullptr);

		void SaveState() override;
		void LoadState() override;

		void Update(GLFWwindow* window) override;
	private:
		bool m_isChopped;
	};
}