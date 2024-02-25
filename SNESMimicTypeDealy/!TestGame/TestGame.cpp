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
#include "../Objects/GUI/Menus/GUIMenu.h"
#include "../Objects/Instantiate/LevelObjectHandler.h"
#include "../Resources/Save/SaveManager.h"
#include "./Objects/Environment/Plants/Tree.h"
#include "./InputDisplay/DisplayIconManager.h"

#include "../Objects/GUI/Text/TextRenderer.h"

#if _DEBUG
#include "../Debug/LevelBuilder/LevelBuilder.h"
#endif

#include "./Level/LevelManager.h"
#include <thread>
#include "./Objects/Enemies/Enemy.h"

namespace GAME_NAME
{
	using namespace MathUtils;
	using namespace Objects;
	using namespace Resources;

	TestGame* GAME_NAME::TestGame::INSTANCE(nullptr);

	std::shared_ptr<Objects::Player::Player> TestGame::ThePlayer;

	GLFWwindow* TestGame::FirstWindow;
	
	bool TestGame::m_gamePaused = false;

	GlobalLevelData* TestGame::m_globalLevelData = nullptr;

	unsigned int pauseMenu_buttonIdOffset = 0;
	void pauseMenu_guiCallback(int id)
	{
		id -= pauseMenu_buttonIdOffset;
		if (id == 0)
		{
			TestGame::INSTANCE->TogglePauseState();
		}
	}

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{

		InputManager::GetJoystick();

		if (InputManager::GetKeyUpDown(DEFAULT_PAUSE_GAME) & InputManager::KEY_STATE_PRESSED)
		{
			TogglePauseState();
		}

		MusicSync::MusicSync::Update();	//Update things that sync to the beat of the current song.

		m_gameCamera->Update(ThePlayer->GetPosition());

		//std::cout << Time::GameTime::GetScaledDeltaTime() << std::endl;
	}

	void TestGame::Init(GLFWwindow* window)
	{

		INSTANCE = this;
		m_gameCamera = new GAME_NAME::Camera::GameCamera();

		FirstWindow = window;

		m_camera = m_gameCamera;

		SaveManager::SetCurrentFile("default_s");

		LoadLevel("/town_1", LEVEL_DATA_TEXTURES_BACKGROUND);

		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);

		LoadLevel("/town_1", (GAME_NAME::Game::Game::LEVEL_DATA)(LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_ALL));

		Mappings::LoadObjectsWithDefaultMapping("/town_1");
		RenderFront = true;

		std::string data_0("null");
		SaveManager::GetSaveString("data_0", data_0);

		SaveManager::SaveString("testing string", "data_0");

		Input::DisplayIconManager::CreateKeyDisplayObjects();

	}

	void TestGame::LateUpdate(GLFWwindow* window)
	{
		CollisionManager::UpdateAndClearBuffers();
		Input::DisplayIconManager::AttemptHideIcons();
	}

	void TestGame::InitLevel(GAME_NAME::Game::Level level)
	{
#if _DEBUG
		Debug::LevelBuilder::LevelBuilder::InitLevelBuilderAssets(this);
#endif

		ThePlayer = std::make_shared<Objects::Player::Player>(level.PlayerStartPosition);
		Rendering::Renderer::LoadActiveObject(ThePlayer.get(), 2); //Spawn in the player on Active Layer 2.
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

		//Clear the current global level data.
		delete m_globalLevelData;
		m_globalLevelData = new GlobalLevelData(level.Path);

		//GameObject* leaf = Instantiate::LevelObjectHandler::GetLevelObject("leaf_particle_objects", "leaf_1");
		//leaf->SetPosition(ThePlayer->GetPosition());

		//GAME_NAME::Objects::Enemies::Enemy* enemy = new GAME_NAME::Objects::Enemies::Enemy(Vec2(100, 51), Vec2(32,64), Renderer::GetSprite(SpriteBase(10)));
	
		//Renderer::LoadActiveObject(enemy);
	}



	void TestGame::TogglePauseState()
	{
		m_gamePaused = !m_gamePaused;
		
		if (m_gamePaused)
		{
			pauseMenu_buttonIdOffset = GUI::Menus::GUIMenu::LoadMenu("/pause", new std::function(pauseMenu_guiCallback));
			Rendering::Renderer::UpdateObjects = false;
		}
		else {
			GUI::Menus::GUIMenu::RemoveLastMenu();
			Rendering::Renderer::UpdateObjects = true;
		}
	}

}