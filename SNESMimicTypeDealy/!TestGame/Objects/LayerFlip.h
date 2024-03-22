#pragma once
#include "../../Components/IComponent.h"

namespace GAME_NAME::Objects
{
	/// <summary>
	/// A layer flip is an object that changes between two layers based on if the player is above or below it.
	/// </summary>
	class LayerFlip
		: public Components::IComponent
	{
	public:
		/// <summary>
		/// Create a layer flip. Flip offset is the amount on the Y axis to offset from the center of the object to stop flipping.
		/// </summary>
		/// <param name="flipOffset"></param>
		LayerFlip(float flipOffset) : m_flipOffset(flipOffset) {};
		void Update(GLFWwindow* window, Objects::GameObject* object);
		void Init(Objects::GameObject* object);

		~LayerFlip();
	private:
		float m_flipOffset;
		GameObject* m_upperLayer;
	};
}