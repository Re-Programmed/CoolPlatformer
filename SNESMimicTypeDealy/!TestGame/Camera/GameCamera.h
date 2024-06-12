#pragma once
#include "../../Rendering/Camera/Camera.h"
#include "../../Utils/Math/Vec2.h"

namespace GAME_NAME
{
	namespace Camera
	{
		using namespace MathUtils;

		constexpr double CameraSpeed = 5.0;

		/// <summary>
		/// Camera for the game to use.
		/// </summary>
		class GameCamera
			: public Rendering::Camera::Camera
		{
		public:
			GameCamera();

			/// <summary>
			/// Update should be called every frame to lerp the camera to the player.
			/// </summary>
			/// <param name="playerPos"></param>
			void Update(const Vec2& playerPos);

			/// <summary>
			/// If set true, the camera will lock to the player rather than using a smooth follow.
			/// </summary>
			/// <param name="followPlayerExact"></param>
			inline void SetFollowPlayerExact(bool followPlayerExact)
			{
				m_followPlayerExact = followPlayerExact;
			}

			/// <summary>
			/// Used to lerp the camera's zoom and create a zooming in or out effect.
			/// </summary>
			/// <param name="target"></param>
			inline void SetTargetZoom(float target)
			{
				m_targetZoom = target;
			}

			inline void SetOffset(Vec2 offset)
			{
				m_offset = offset;
			}
		private:
			bool m_followPlayerExact;
			float m_targetZoom;
			Vec2 m_offset;
		};
	}
}