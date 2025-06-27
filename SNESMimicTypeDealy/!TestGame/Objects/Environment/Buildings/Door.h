#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Components/Physics/Collision/StaticBoxCollider.h"
#include "../../../../CustomCompileOptions.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	using namespace GAME_NAME::Components::Physics::Collision;

	/// <summary>
	/// A door to a building that can open and close if the player is near.
	/// </summary>
	class Door
		: public GameObject
	{
	public:
		/// <summary>
		/// Creates a door.
		/// </summary>
		/// <param name="position">Position of the door.</param>
		/// <param name="scale">Scale of the door.</param>
		/// <param name="sprite">Cloesd sprite for the door.</param>
		/// <param name="openSprite">Open sprite for the door.</param>
		/// <param name="doorOpenDistance">How close the player must be to open the door.</param>
		/// <param name="rotation">Rotation.</param>
		Door(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Rendering::Sprite* openSprite, float doorOpenDistance = DEFAULT_DOOR_OPEN_DISTANCE, float rotation = 0.f)
			: GameObject(position, scale, sprite, rotation), m_openSprite(openSprite), m_doorOpenDistance(doorOpenDistance), m_boxCollider(new StaticBoxCollider())
		{
			m_boxCollider->Init(this);
		};

		Door() = default;
		
		/// <summary>
		/// Called each frame to check if the door should open.
		/// </summary>
		/// <param name="window"></param>
		void Update(GLFWwindow* window) override;

		~Door()
		{
			delete m_boxCollider;
			GameObject::~GameObject();
		};
	private:
		/// <summary>
		/// The doors collider, only updated when the door is shut.
		/// </summary>
		StaticBoxCollider* const m_boxCollider;

		/// <summary>
		/// How close the player needs to get to open this door.
		/// </summary>
		const float m_doorOpenDistance;
		/// <summary>
		/// Holds a pointer to the opposite sprite of what the doors current state is. Ex. if the door is open, the m_openSprite will be the closed one.
		/// </summary>
		std::shared_ptr<GAME_NAME::Rendering::Sprite> m_openSprite;

		/// <summary>
		/// True if the door is open.
		/// </summary>
		bool m_isOpen = false;

		/// <summary>
		/// Opens the door by setting m_isOpen and flipping the sprite.
		/// Only does so if m_isOpen is false.
		/// </summary>
		void open();
		/// <summary>
		/// Closes the door by setting m_isOpen and flipping the sprite.
		/// Only does so if m_isOpen is true.
		/// </summary>
		void close();

		/// <summary>
		/// Utility function that sets the current door sprite to the m_openSprite and replaces the open sprite with the current door sprite.
		/// The doors current sprite will either be open or closed based on m_isOpen and the m_openSprite will be the opposite of what the door
		/// is currently.
		/// </summary>
		void flipSprite();
	};
}