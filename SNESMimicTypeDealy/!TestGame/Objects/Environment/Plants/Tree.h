#pragma once
#include "../../../../Objects/Helpers/Interactable.h"
#include "../../../../Objects/GameObjectState.h"
#include "../../../../Input/InputManager.h"
#include "../../Player/Player.h"

#define TREE_INTERACT_KEY PLAYER_INTERACT

namespace GAME_NAME::Objects::Environment::Plants
{

	/// <summary>
	/// A tree that can be climbed and chopped down to harvest wood, leaves, and more.
	/// </summary>
	class Tree : public Interactable, public GameObjectState
	{
	public:
		/// <summary>
		/// Create a tree with position, scale, and two sprites.
		/// </summary>
		Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, Rendering::Sprite* choppedSprite);

		~Tree()
		{
			delete m_animator;
		}

		/// <summary>
		/// Saves the trees state to the current save. (Weather its already been chopped down.)
		/// </summary>
		void SaveState() override;
		/// <summary>
		/// Loads the trees state from the current save. (Weather its already been chopped down.)
		/// </summary>
		void LoadState() override;

		void Update(GLFWwindow* window) override;

		/// <summary>
		/// Chops down the tree and calls respective methods to drop items, update textures, and spawn particles.
		/// </summary>
		/// <returns>Returns true if the tree was sucessfully chopped. If the tree was unable to be chopped for any reason, returns false.</returns>
		bool Chop();

		bool Rustle();

	protected:
		void onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state) override;
	private:
		/// <summary>
		/// The sprite that displays after the tree has been chopped, or, if the tree is already chopped, the sprite to display when the tree is alive.
		/// </summary>
		std::shared_ptr<Rendering::Sprite> m_choppedSprite;
		
		/// <summary>
		/// Is the tree cut down already?
		/// </summary>
		bool m_isChopped;

		/// <summary>
		/// Number of times this tree has been rustled.
		/// </summary>
		char m_rustles;
		float m_rustleCounter;

		/// <summary>
		/// Sets if the tree has been chopped down without dropping items and only updating graphics.
		/// </summary>
		/// <param name="chopped"></param>
		void setChopped(bool chopped);

		AnimatorComponent* m_animator;
	};
}