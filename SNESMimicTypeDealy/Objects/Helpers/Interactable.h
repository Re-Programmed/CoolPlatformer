#pragma once
#include "../GameObject.h"
#include "../../Input/InputManager.h"
#include "../../!TestGame/TestGame.h"

namespace GAME_NAME::Objects
{
	/// <summary>
	/// An object the player can interact with when within a certain range and pressing a certain key.
	/// </summary>
	class Interactable
		: public GameObject
	{
	public:
		Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation = 0.f, bool useBoundingBox = false);
		Interactable(keyRef interactKey, InputManager::KEY_STATE keyStateCheck, float interactionRadius, Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation = 0.f);

		void Update(GLFWwindow* window) override;
	protected:
		virtual void onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state) = 0;

	private:
		const bool m_useBoundingBox;
		const float m_interactionRadius;

		const keyRef m_interactKey;
		const InputManager::KEY_STATE m_keyStateCheck;
	};
}