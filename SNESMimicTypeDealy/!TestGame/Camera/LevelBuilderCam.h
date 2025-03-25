#pragma once

#if _DEBUG

#include "./GameCamera.h"

namespace GAME_NAME
{
	namespace Camera
	{
		using namespace MathUtils;

		/// <summary>
		/// Camera for the game to use.
		/// </summary>
		class LevelBuilderCam
			: public GAME_NAME::Camera::GameCamera
		{
		public:
			LevelBuilderCam(Vec2 pos, float zoom);

			/// <summary>
			/// Update should be called every frame to lerp the camera to the player.
			/// </summary>
			/// <param name="playerPos"></param>
			void Update(const Vec2& playerPos);
		};
	}
}

#endif