#include "RotatingPlatform.h"

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

		double eTime = GameTime::GetElapsedTime() * m_rotationSpeed;

		float xPos = std::cos(eTime + m_rotationOffset) * m_rotationRadius;
		float yPos = std::sin(eTime + m_rotationOffset) * m_rotationRadius;

		SetPosition(Vec2(xPos + m_rotationOrigin.X, yPos + m_rotationOrigin.Y));
	}

}