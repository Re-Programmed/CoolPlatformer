#include "GameCamera.h"
#include "../../Utils/Time/GameTime.h"
#include "../../Rendering/Sprite.h"

namespace GAME_NAME
{
	namespace Camera
	{
		GameCamera::GameCamera()
			: Rendering::Camera::Camera(Vec2::Zero, 1.f)
		{

		}

		constexpr float HalfTResX = TargetResolutionX / 2.f;
		constexpr float HalfTResY = TargetResolutionY / 2.f;

		void GameCamera::Update(Vec2 playerPos)
		{
			if (m_followPlayerExact)
			{
				//SetPosition(Vec2(playerPos.X - HalfTResX, playerPos.Y - HalfTResY));
				//return;
			}

			const double sdt = GAME_NAME::Utils::Time::GameTime::GetScaledDeltaTime();

			float resX = HalfTResX * (1 / m_zoom);
			float resY = HalfTResY * (1 / m_zoom);

			Vec2 l = Vec2(std::lerp(m_position.X + resX, playerPos.X, CameraSpeed * sdt) - resX, std::lerp(m_position.Y + resY, playerPos.Y, CameraSpeed * sdt) - resY);

			SetPosition(l);
		}
	}
}