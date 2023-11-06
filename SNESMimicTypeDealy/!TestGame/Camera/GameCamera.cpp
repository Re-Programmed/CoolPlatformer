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

			Vec2 l = Vec2(std::lerp(m_position.X + HalfTResX, playerPos.X, CameraSpeed * sdt) - HalfTResX, std::lerp(m_position.Y + HalfTResY, playerPos.Y, CameraSpeed * sdt) - HalfTResY);

			SetPosition(l);
		}
	}
}