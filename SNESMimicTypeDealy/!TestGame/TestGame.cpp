#include "TestGame.h"
#include "../Rendering/Camera/MoveableCamera.h"
#include "../Utils/Math/Vec2.h"
#include "./Objects/DebugObject.h"
#include "../Objects/GameObject.h"
#include "../Components/IComponent.h"
#include "./Mappings.h"

namespace GAME_NAME
{
	using namespace MathUtils;
	using namespace Objects;
	using namespace Resources;

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{

	}

	void TestGame::Init(GLFWwindow* window)
	{
		m_camera = new Rendering::Camera::MoveableCamera(window, Vec2::Zero, 1.f, 10.f);

		loadLevel("/testing", LEVEL_DATA_ALL);

		Mappings::LoadObjectsWithDefaultMapping("/testing");
	}

	void TestGame::LateUpdate(GLFWwindow* window)
	{

	}

}