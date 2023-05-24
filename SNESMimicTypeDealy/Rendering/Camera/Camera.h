#pragma once
#include "../../Utils/Math/Vec2.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <iostream>

constexpr float minimumCameraZoom = 0.3f;
constexpr float maximumCameraZoom = 2.f;

#define LIMIT_CAMERA_NEGATIVE true

namespace GAME_NAME
{

	namespace Rendering
	{
		namespace Camera
		{
			using namespace MathUtils;
			class Camera
			{
			public:
				Camera(Vec2 position, float zoom);

				virtual void Update(GLFWwindow* window) {};

				Vec2 GetPosition();
				void SetPosition(Vec2 pos);

			

				float GetZoom();
				void SetZoom(float zoom);

				/// <summary>
				/// Adds an amount to the current zoom.
				/// </summary>
				void Zoom(const float amount);

				void Translate(Vec2 translation);
		

			
				
			private:
				Vec2 m_position;
				float m_zoom = 1.f;

			};
		}
	}
}