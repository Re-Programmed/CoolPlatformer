#include "RotatingPlatform.h"

#include "../../../MusicSync/MusicSync.h"

namespace GAME_NAME::Objects::Platforms
{
	RotatingPlatform::RotatingPlatform(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Vec2 rotationCenter, double speed, double offset)
		: BasicMovingPlatform(position, scale, sprite), m_rotationOrigin(rotationCenter), m_rotationRadius(Vec2::Distance(position, rotationCenter)), m_rotationSpeed(speed), m_rotationOffset(offset)
	{

	}

	void RotatingPlatform::Update(GLFWwindow* window)
	{
		BasicMovingPlatform::Update(window);

		using namespace Utils::Time;

		double eTime = MusicSync::MusicSync::GetElapsedTimeWithinBeats(m_rotationSpeed);

		float xPos = std::cos(eTime * 2 * 3.141592653589793 + m_rotationOffset) * m_rotationRadius;
		float yPos = std::sin(eTime * 2 * 3.141592653589793 + m_rotationOffset) * m_rotationRadius;

		SetPosition(Vec2(xPos + m_rotationOrigin.X, yPos + m_rotationOrigin.Y));
	}

}