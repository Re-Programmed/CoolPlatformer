#include "GameCamera.h"
#include "../../Utils/Time/GameTime.h"
#include "../../Rendering/Sprite.h"

#if _DEBUG
#include "../../Input/InputManager.h"
#endif

namespace GAME_NAME
{
	namespace Camera
	{
		GameCamera::GameCamera()
			: Rendering::Camera::Camera(Vec2::Zero, 1.f), m_targetZoom(-1), m_offset({ 0, 0 }), m_followPlayerExact(false), m_deadzoneRadius(30.f)
		{

		}

		constexpr float HalfTResX = TargetResolutionX / 2.f;
		constexpr float HalfTResY = TargetResolutionY / 2.f;

		void GameCamera::Update(const Vec2& playerPos)
		{
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

			/*if (m_followPlayerExact)
			{
				//SetPosition(Vec2(playerPos.X - HalfTResX, playerPos.Y - HalfTResY));
				//return;
			}*/

			const double sdt = GAME_NAME::Utils::Time::GameTime::GetScaledDeltaTime();

			if (m_targetZoom > 0)
			{
				//Lerp zoom.
				SetZoom(std::lerp(m_zoom, m_targetZoom, (float)CameraSpeed / 8.f * (float)sdt));
			}

			float resX = HalfTResX * (1 / m_zoom);
			float resY = HalfTResY * (1 / m_zoom);

			if (m_deadzoneRadius > 0.f)
			{
				//X Deadzone
				if (!(playerPos.X + m_offset.X > m_position.X + resX + m_deadzoneRadius || playerPos.X + m_offset.X < m_position.X + resX - m_deadzoneRadius))
				{
					//Y Deadzone
					if (std::abs(playerPos.Y + m_offset.Y - m_position.Y - resY) < m_deadzoneRadius * 4.f)
					{
						return;
					}
				}

			}

			float deadzoneXAdj = (playerPos.X > m_position.X + resX ? -m_deadzoneRadius : m_deadzoneRadius);
			float deadzoneYAdj = (playerPos.Y > m_position.Y + resY ? -m_deadzoneRadius : m_deadzoneRadius);

			Vec2 l = Vec2(std::lerp(m_position.X + resX, playerPos.X + m_offset.X + deadzoneXAdj, (float)(CameraSpeed * sdt)) - resX, std::lerp(m_position.Y + resY, playerPos.Y + m_offset.Y + deadzoneYAdj, (float)(CameraSpeed * sdt)) - resY);

			SetPosition(l);
		}

	}
}