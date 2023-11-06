#include "../../../Components/Physics/Collision/Helpers/BasicMovingPlatform.h"
#include "../../../Utils/Time/GameTime.h"

#ifndef _ROTATING_PLATFORM_DEF
#define _ROTATING_PLATFORM_DEF

namespace GAME_NAME::Objects::Platforms
{
	using namespace Components::Physics::Collision;

	/// <summary>
	/// A platform that rotates about a point at some speed.
	/// </summary>
	class RotatingPlatform : public Components::Physics::Collision::BasicMovingPlatform
	{
		
	public:
		/// <summary>
		/// Rotating Platform.
		/// </summary>
		/// <param name="position">Global position of the platform.</param>
		/// <param name="scale">Scale of the platform.</param>
		/// <param name="sprite">Sprite to use.</param>
		/// <param name="rotationCenter">The origin of rotation.</param>
		/// <param name="speed">The speed to rotate at.</param>
		RotatingPlatform(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 rotationCenter, double speed = 1.0, double offset = 0.0);

		/// <summary>
		/// Called each frame.
		/// </summary>
		/// <param name="window">The current game window.</param>
		void Update(GLFWwindow* window);

	private:
		const Vec2 m_rotationOrigin;	//The center of rotation.
		const float m_rotationRadius;	//The distance to rotate out from the center.
		const double m_rotationSpeed;	//The speed at which to rotate.
		const double m_rotationOffset;	//How much to offset the rotation by in radians.
	};
}

#endif