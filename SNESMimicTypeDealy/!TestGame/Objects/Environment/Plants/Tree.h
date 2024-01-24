#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Objects/GameObjectState.h"

namespace GAME_NAME::Objects::Environment::Plants
{
	/// <summary>
	/// A tree that can be climbed and chopped down to harvest wood, leaves, and more.
	/// </summary>
	class Tree : public GameObject, public GameObjectState
	{
	public:
		/// <summary>
		/// Create a tree with position, scale, and two sprites.
		/// </summary>
		Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, Rendering::Sprite* choppedSprite);

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
	private:
		/// <summary>
		/// The sprite that displays after the tree has been chopped, or, if the tree is already chopped, the sprite to display when the tree is alive.
		/// </summary>
		Rendering::Sprite* m_choppedSprite;
		
		/// <summary>
		/// Is the tree cut down already?
		/// </summary>
		bool m_isChopped;

		/// <summary>
		/// Sets if the tree has been chopped down without dropping items and only updating graphics.
		/// </summary>
		/// <param name="chopped"></param>
		void setChopped(bool chopped);
	};
}