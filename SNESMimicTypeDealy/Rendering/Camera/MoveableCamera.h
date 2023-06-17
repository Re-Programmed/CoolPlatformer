#pragma once
#include "Camera.h"
#include "../../Input/InputManager.h"
#include "../../Utils/Math/Vec2.h"
#include "../../Utils/ConstUpdateable.h"

#define ZOOM_SPEED 2.f

namespace GAME_NAME
{
	namespace Rendering
	{
		namespace Camera
		{
			/// <summary>
			/// Not for game use, just testing!
			/// </summary>
			class MoveableCamera :
				public Camera, public GAME_NAME::Utils::ConstUpdateable
			{
			public:
				MoveableCamera();
				MoveableCamera(GLFWwindow* window, MathUtils::Vec2 position, float zoom, float speed);

				void Update(GLFWwindow* window);
			private:
				float m_speed;
			};
		}
	}
}