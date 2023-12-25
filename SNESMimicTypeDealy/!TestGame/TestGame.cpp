#include "TestGame.h"
#include "../Rendering/Camera/MoveableCamera.h"
#include "../Utils/Math/Vec2.h"
#include "../Objects/GameObject.h"
#include "../Components/IComponent.h"
#include "./Camera/GameCamera.h"
#include "./Objects/Environment/CloudGenerator.h"
#include "./Objects/Environment/BackgroundObjects.h"
#include "../Settings/AppDataFileManager.h"
#include "../Settings/SettingsGlobals.h"
#include "../MusicSync/MusicSync.h"
#include "./Objects/Platforms/RotatingPlatform.h"
#include "./Mappings.h"

#if _DEBUG
#include "../Debug/LevelBuilder/LevelBuilder.h"
#endif

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
		InputManager::GetJoystick();

		MusicSync::MusicSync::Update();	//Update things that sync to the beat of the current song.

		m_gameCamera->Update(ThePlayer->GetPosition());
		GAME_NAME::Game::Game::Update(window); /*Must be at the bottom of update method*/

		//std::cout << Time::GameTime::GetScaledDeltaTime() << std::endl;
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
#if _DEBUG
		Debug::LevelBuilder::LevelBuilder::InitLevelBuilderAssets(this);
#endif

		ThePlayer = std::make_shared<Objects::Player::Player>(level.PlayerStartPosition);
		Rendering::Renderer::LoadActiveObject(ThePlayer.get(), 1); //Spawn in the player on Active Layer 1.
		std::srand(ThePlayer->GetPosition().X + ThePlayer->GetPosition().Y + static_cast<int>(glfwGetTime()));

		MusicSync::MusicSync::SetCurrentSong(134, 2);

		glClearColor(level.BackgroundColor.X, level.BackgroundColor.Y, level.BackgroundColor.Z, 1.f);
		/*glColor3f(/ X / Y / Z); CREATES A REALLY COOL FOG EFFECT!*/
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