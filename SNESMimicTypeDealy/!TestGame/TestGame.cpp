#include "TestGame.h"
#include "../Rendering/Camera/MoveableCamera.h"
#include "../Utils/Math/Vec2.h"
#include "../Objects/GameObject.h"
#include "../Components/IComponent.h"
#include "./Mappings.h"
#include "./Camera/GameCamera.h"
#include "./Objects/Environment/CloudGenerator.h"
#include "./Objects/Environment/BackgroundObjects.h"
#include "../Settings/AppDataFileManager.h"
#include "../Settings/SettingsGlobals.h"
#include "../MusicSync/MusicSync.h"

#include <thread>

namespace GAME_NAME
{
	using namespace MathUtils;
	using namespace Objects;
	using namespace Resources;

	TestGame* GAME_NAME::TestGame::INSTANCE(nullptr);

	std::shared_ptr<Objects::Player::Player> TestGame::ThePlayer;

	GLFWwindow* TestGame::FirstWindow;

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{
		MusicSync::MusicSync::Update();	//Update things that sync to the beat of the current song.

		m_gameCamera->Update(ThePlayer->GetPosition());
		GAME_NAME::Game::Game::Update(window); /*Must be at the bottom of update method*/
	}

	void TestGame::Init(GLFWwindow* window)
	{
		std::thread appDataThread = std::thread([]() {
			AppData::AppDataFileManager::CreateAppDataFiles();

			//Load Saved Global Settings
			AppData::Settings::SettingsGlobals::LoadAppDataVariables();
		});

		INSTANCE = this;
		m_gameCamera = new GAME_NAME::Camera::GameCamera();

		FirstWindow = window;

		m_camera = m_gameCamera;

		LoadLevel("/town_1", LEVEL_DATA_TEXTURES_BACKGROUND);

		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);

		LoadLevel("/town_1", (GAME_NAME::Game::Game::LEVEL_DATA)(LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_ALL));

		Mappings::LoadObjectsWithDefaultMapping("/town_1");
		RenderFront = true;

		if (appDataThread.joinable()) { appDataThread.join(); }
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
/*
		GameObject hillTiles[1]{
			GameObject(Vec2::Zero, Vec2::One * 16, Renderer::GetSprite(10))
		};

		Environment::BackgroundObjects::TiledBGObject(hillTiles, 1, 0.5f, FirstWindow);
		*/
	}

}