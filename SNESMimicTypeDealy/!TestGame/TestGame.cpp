#include "TestGame.h"
#include "../Rendering/Camera/MoveableCamera.h"
#include "../Utils/Math/Vec2.h"
namespace GAME_NAME
{
	using namespace MathUtils;

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{

	}

	void TestGame::Init(GLFWwindow* window)
	{
		m_camera = new Rendering::Camera::MoveableCamera(window, Vec2::Zero, 1.f, 10.f);
	}

	void TestGame::LateUpdate(GLFWwindow* window)
	{

	}

}