#include "SaggingObject.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	constexpr float SAG_SEGMENTS_3[3] = { 2.5f, 5.f, 2.5f };
	constexpr float SAG_SEGMENTS_5[5] = { 1.f, 2.f, 4.f, 2.f, 1.f };
	constexpr float SAG_SEGMENTS_7[7] = { 0.5f, 1.f, 2.f, 3.f, 2.f, 1.f, 0.5f };

	
	SaggingObject::SaggingObject(Vec2 position, Vec2 scale, Sprite* sprite, uint8_t sagSegments)
		: GameObject(position, scale, sprite)
	{
		m_sagObjects.resize(sagSegments);

		if (sagSegments % 2 == 0) { sagSegments++; }
		if (sagSegments < 3) { sagSegments = 3; }
		if (sagSegments > 7) { sagSegments = 7; }

		float currentOffset = 0.f;
		for (int i = 0; i < sagSegments; i++)
		{
			float scaleX = 0.f;
			switch (sagSegments)
			{
			case 3:
				scaleX = SAG_SEGMENTS_3[i];
				break;
			case 5:
				scaleX = SAG_SEGMENTS_5[i];
				break;
			case 7:
			default:
				scaleX = SAG_SEGMENTS_7[i];
				break;
			}

			GameObject* sagObject = new GameObject(m_position + Vec2{ currentOffset, 0.f }, Vec2{ scaleX, m_scale.Y }, sprite);
			m_sagObjects.push_back(sagObject);
			
			currentOffset += scaleX;
		}
	}

	void SaggingObject::Update(GLFWwindow* window)
	{

	}

	void SaggingObject::Render(const Vec2& cameraPosition)
	{

	}
}


