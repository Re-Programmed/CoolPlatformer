#pragma once
#include "../../Rendering/Camera/Camera.h"
#include "../../Utils/Math/Vec2.h"

#include "../../Objects/GameObject.h"

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
			void Update(Vec2 playerPos);

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


			inline void LockCamera(Objects::GameObject* lockObject)
			{
				m_lockedObject = lockObject;
			}

			inline void LockCamera(Vec2 lockPosition)
			{
				m_locked = lockPosition;
			}

			inline void UnlockCamera()
			{
				m_locked = Vec2::Zero;
				m_lockedObject = nullptr;
			}

		private:
			bool m_followPlayerExact;
			float m_targetZoom;
			float m_deadzoneRadius;
			Vec2 m_offset;

			Vec2 m_locked; Objects::GameObject* m_lockedObject;
		};
	}
}