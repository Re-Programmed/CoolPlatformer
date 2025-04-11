#if _DEBUG

#include "LevelBuilderCam.h"
#include "../../Utils/Time/GameTime.h"
#include "../../Rendering/Sprite.h"
#include "../../Input/InputManager.h"

namespace GAME_NAME::Camera
{
	LevelBuilderCam::LevelBuilderCam(Vec2 pos, float zoom)
		: m_offset(0), m_targetPos(pos)
	{
		m_position = pos;
		m_zoom = zoom;
	}

	constexpr float HalfTResX = TargetResolutionX / 2.f;
	constexpr float HalfTResY = TargetResolutionY / 2.f;

	void LevelBuilderCam::Update(const Vec2& playerPos)
	{
		if (m_position.X < 0 || m_position.Y < 0) { m_targetPos = playerPos; }

#if _DEBUG
		if (InputManager::GetKey(GLFW_KEY_L))
		{
			SetTargetZoom(1.f);
		}

		if (InputManager::GetKey(GLFW_KEY_K))
		{
			SetTargetZoom(0.25f);
		}
#endif
		const double sdt = GAME_NAME::Utils::Time::GameTime::GetScaledDeltaTime();

		if (InputManager::GetKey(GLFW_KEY_A))
		{
			m_targetPos += Vec2::MinusOneX * sdt;
		}

		if (InputManager::GetKey(GLFW_KEY_D))
		{
			m_targetPos += Vec2::OneX * sdt;
		}

		if (InputManager::GetKey(GLFW_KEY_W))
		{
			m_targetPos += Vec2::OneY;
		}

		if (InputManager::GetKey(GLFW_KEY_S))
		{
			m_targetPos += Vec2::MinusOneY;
		}

		/*if (m_followPlayerExact)
		{
			//SetPosition(Vec2(playerPos.X - HalfTResX, playerPos.Y - HalfTResY));
			//return;
		}*/


		if (m_targetZoom > 0)
		{
			//Lerp zoom.
			SetZoom(std::lerp(m_zoom, m_targetZoom, (float)CameraSpeed / 8.f * (float)sdt));
		}

		float resX = HalfTResX * (1 / m_zoom);
		float resY = HalfTResY * (1 / m_zoom);

		Vec2 l = Vec2(std::lerp(m_position.X + resX, m_targetPos.X + m_offset.X, (float)(CameraSpeed * sdt)) - resX, std::lerp(m_position.Y + resY, m_targetPos.Y + m_offset.Y, (float)(CameraSpeed * sdt)) - resY);

		SetPosition(l);
	}

}

#endif