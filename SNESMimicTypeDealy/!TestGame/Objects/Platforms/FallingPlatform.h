#include "../../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

using namespace GAME_NAME::Components::Physics::Collision;

namespace GAME_NAME::Objects::Platforms
{
	/// <summary>
	/// A platform that falls when something lands on it.
	/// </summary>
	class FallingPlatform : public StaticBoxCollisionObject
	{
	public:
		/// <summary>
		/// Create a falling platform with position, scale, and sprite.
		/// </summary>
		/// <param name="position"></param>
		/// <param name="scale"></param>
		/// <param name="sprite"></param>
		FallingPlatform(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float fallDelay = 0.f);

	protected:
		/// <summary>
		/// onCollision checks if an object lands on the platform, causing it to fall.
		/// </summary>
		/// <param name="push"></param>
		/// <param name="object"></param>
		/// <param name="collider"></param>
		/// <returns></returns>
		static bool onCollision(Vec2 push, Objects::GameObject* object, Objects::GameObject* collider);

		void Update(GLFWwindow* window) override;
	private:
		/// <summary>
		/// Represents the speed at which the current falling platform is falling.
		/// </summary>
		float m_gravity = 0.f;

		/// <summary>
		/// The time spent in air before the platform falls.
		/// Necessary if the player is to jump off of the platform.
		/// </summary>
		const float m_fallDelay;
		float m_fallCounter = 0.f;

		/// <summary>
		/// The Y position the platform is spawned at, used for resetting the platform after it has fallen.
		/// </summary>
		const float m_storedInitY;
	};
}