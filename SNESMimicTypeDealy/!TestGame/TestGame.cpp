#include "TestGame.h"
#include "../Rendering/Camera/MoveableCamera.h"
#include "../Utils/Math/Vec2.h"
#include "../Objects/GameObject.h"
#include "../Components/IComponent.h"
#include "./Mappings.h"
#include "./Camera/GameCamera.h"
#include "./Objects/Environment/CloudGenerator.h"

namespace GAME_NAME
{
	using namespace MathUtils;
	using namespace Objects;
	using namespace Resources;

	TestGame* GAME_NAME::TestGame::INSTANCE(nullptr);

	std::shared_ptr<Objects::Player::Player> TestGame::ThePlayer;

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{
		m_gameCamera->Update(ThePlayer->GetPosition());
		GAME_NAME::Game::Game::Update(window); /*Must be at the bottom of update method*/
	}

	void TestGame::Init(GLFWwindow* window)
	{
		INSTANCE = this;
		m_gameCamera = new GAME_NAME::Camera::GameCamera();

		m_camera = m_gameCamera;

		loadLevel("/testing", LEVEL_DATA_ALL);

		Mappings::LoadObjectsWithDefaultMapping("/testing");
		RenderFront = true;
	}

	void TestGame::LateUpdate(GLFWwindow* window)
	{
		CollisionManager::UpdateAndClearBuffers();
	}

	void TestGame::InitLevel(GAME_NAME::Game::Level level)
	{
		ThePlayer = std::make_shared<Objects::Player::Player>(level.PlayerStartPosition);
		Rendering::Renderer::LoadActiveObject(ThePlayer.get());
		std::srand(ThePlayer->GetPosition().X + ThePlayer->GetPosition().Y + static_cast<int>(glfwGetTime()));
		//Play Music

		//Environment::CloudGenerator::GenerateClouds(50);
	}

}