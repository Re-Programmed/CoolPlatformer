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
			void Update(Vec2 playerPos);
		private:
		};
	}
}