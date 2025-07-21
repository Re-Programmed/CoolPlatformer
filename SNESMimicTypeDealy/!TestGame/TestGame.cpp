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
#include "../Objects/Particles/ParticleEmitter.h"

#include "./Cutscenes/DialogueManager.h"

#include "./Objects/Environment/Effects/GlitchedRegion.h"

#include "./Objects/Environment/Levels/Town1Manager.h"

#include "./Items/Inventories/InventoryContainerRenderer.h"

#include "./Cutscenes/CutsceneManager.h"

#include "../Objects/GUI/Text/TextRenderer.h"

#if _DEBUG
#include "../Debug/LevelBuilder/LevelBuilder.h"
#include "./Debug/DebugCommands.h"
#include "./Camera/LevelBuilderCam.h"
#endif

#include "./Level/LevelManager.h"
#include <thread>
#include "./Objects/Enemies/Types/LeftRightEnemy.h"

#include "../Objects/StateSaver.h"

#include "./SettingsManager.h"

#include "./Level/MainMenu/MainMenuManager.h"
#include "./Level/Introduction/IntroductionLevelManager.h"

//TESTING:
#include "./Objects/Environment/Buildings/Door.h"
#include "./Objects/Environment/Buildings/FrontWall.h"

#include "../Objects/GUI/GUIManager.h"
#include "../Rendering/Lighting/SimpleLightingManager.h"

#define SKIP_MAIN_MENU
//#define SKIP_INTRODUCTION

namespace GAME_NAME
{
	using namespace MathUtils;
	using namespace Objects;
	using namespace Resources;

	TestGame* GAME_NAME::TestGame::INSTANCE(nullptr);

	std::unique_ptr<LevelSystem> TestGame::m_currentLevelSystem;

	std::shared_ptr<Objects::Player::Player> TestGame::ThePlayer;

	GLFWwindow* TestGame::FirstWindow;
	
	bool TestGame::m_gamePaused = false;

	GlobalLevelData* TestGame::m_globalLevelData = nullptr;

	std::vector<StaticGUIElement*> TestGame::m_pauseMenuObjects;

	std::string Game_nextLevelToLoad = ""; bool Game_nextLevelIsOnlyObjects = false; Vec2 Game_playerNewPos = Vec2{ -1 };
	
	unsigned int pauseMenu_buttonIdOffset = 0; //UNUSED???????
	void pauseMenu_guiCallback(int id)
	{
		std::cout << "ID OF BUTTON: " << id << std::endl; //TESTING BUTTONS.

		//Resume button.
		if (id == 1)
		{
			TestGame::INSTANCE->TogglePauseState();
			return;
		}

		if (id == 2)
		{
			TestGame::INSTANCE->TogglePauseState();
			SettingsManager::CreateSettingsMenu();
			return;
		}

		//Exit button.
		if (id == 0)
		{
			exit(1);
		}
	}

	void GAME_NAME::TestGame::Update(GLFWwindow* window)
	{
		if (!Game_nextLevelToLoad.empty())
		{
			if (Game_nextLevelIsOnlyObjects)
			{
				GAME_NAME::Resources::SaveManager::SetCurrentFile("default_s");

				GAME_NAME::Renderer::ClearObjects();
				Mappings::LoadObjectsWithDefaultMapping(Game_nextLevelToLoad.c_str());

				ThePlayer = std::make_shared<Objects::Player::Player>(Game_playerNewPos);
				Rendering::Renderer::LoadActiveObject(ThePlayer.get(), 2); //Spawn in the player on Active Layer 2.
				LevelManager::LevelCircleAnimation(Vec2{-1}, true);
			}
			else {
				GAME_NAME::Resources::SaveManager::SetCurrentFile("default_s");

				GAME_NAME::Renderer::ClearObjects();
				GAME_NAME::Renderer::ClearTextures();

				LoadLevel(Game_nextLevelToLoad.c_str(), LEVEL_DATA_TEXTURES_BACKGROUND, true);
				LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);
				LoadLevel(Game_nextLevelToLoad.c_str(), static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_ALL xor LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_DATA_LEVEL));
				Mappings::LoadObjectsWithDefaultMapping(Game_nextLevelToLoad.c_str());
				LoadLevel(Game_nextLevelToLoad.c_str(), static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_DATA_LEVEL));
				Cutscenes::DialogueManager::INSTANCE->LoadStoredDialogueSequences(Game_nextLevelToLoad.c_str());
				RenderFront = true;
			}

			Game_nextLevelToLoad = "";
			Game_nextLevelIsOnlyObjects = false;

			return;
		}

#if _DEBUG

		DebugCommands::HandleCommands();

		if (InputManager::GetKeyUpDown(DEBUG_SET_OBJECT_Y) & InputManager::KEY_STATE_PRESSED)
		{
			StateSaver::SaveStates();
			StateSaver::SaveMisc();
		}
		

#endif

		//Update input manager stuff.
		InputManager::UpdateKeyStates();
		InputManager::GetJoystick();

		//Update all cutscenes detection.
		Cutscenes::CutsceneManager::UpdateCutsceneTriggers();

		if (InputManager::GetKeyUpDown(DEFAULT_PAUSE_GAME) & InputManager::KEY_STATE_PRESSED)
		{
			TogglePauseState();
		}

		MusicSync::MusicSync::Update();	//Update things that sync to the beat of the current song.

		//If the player exists, update the game camera with the player's position.
		m_gameCamera->Update(ThePlayer == nullptr ? (m_gameCamera->GetPosition() + Vec2{TargetResolutionX/2, TargetResolutionY/2}) : ThePlayer->GetPosition());

		if (m_currentLevelSystem != nullptr)
		{
			m_currentLevelSystem->Update(window);
		}
	}

	void TestGame::Init(GLFWwindow* window)
	{
		srand(time(NULL));

		INSTANCE = this;
		m_gameCamera = new GAME_NAME::Camera::GameCamera();

		FirstWindow = window;

		m_camera = m_gameCamera;

		//Initilize dialogue systems.
		Cutscenes::DialogueManager::Init();

		SaveManager::SetCurrentFile("default_s");

#ifdef SKIP_MAIN_MENU
#ifdef SKIP_INTRODUCTION
		LoadLevel("/green_region", LEVEL_DATA_TEXTURES_BACKGROUND);
		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);
		LoadLevel("/green_region", static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_ALL xor LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_DATA_LEVEL));
		Mappings::LoadObjectsWithDefaultMapping("/green_region");
		LoadLevel("/green_region", static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_DATA_LEVEL));
		Cutscenes::DialogueManager::INSTANCE->LoadStoredDialogueSequences("/green_region");
		RenderFront = true;
#else
		LoadLevel("/introduction_1", LEVEL_DATA_TEXTURES_BACKGROUND);
		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);
		LoadLevel("/introduction_1", static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_ALL xor LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_DATA_LEVEL));
		Mappings::LoadObjectsWithDefaultMapping("/introduction_1");
		LoadLevel("/introduction_1", static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_DATA_LEVEL));
		Cutscenes::DialogueManager::INSTANCE->LoadStoredDialogueSequences("/introduction_1");
		RenderFront = true;
#endif
#else
		LoadLevel("/main_menu", LEVEL_DATA_TEXTURES_BACKGROUND);
		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);
		LoadLevel("/main_menu", static_cast<GAME_NAME::Game::Game::LEVEL_DATA>(LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_ALL));
		Mappings::LoadObjectsWithDefaultMapping("/main_menu");
		RenderFront = true;
#endif

		/* TESTING OTHER LEVELS
		LoadLevel("/green_region", LEVEL_DATA_TEXTURES_BACKGROUND);

		LoadLevel("/global_assets", LEVEL_DATA_TEXTURES_SPRITES);

		LoadLevel("/green_region", (GAME_NAME::Game::Game::LEVEL_DATA)(LEVEL_DATA_TEXTURES_BACKGROUND xor LEVEL_DATA_ALL));

		Mappings::LoadObjectsWithDefaultMapping("/green_region");
		RenderFront = true;
		*/

		//SAVE DATA TEST.
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
		DebugCommands::RunRecieverThread();
#endif

		//If the LEVEL_NO_PLAYER_FLAG is set, the player will not be created.
		if (!level.Flags.contains(LEVEL_NO_PLAYER_FLAG))
		{
			ThePlayer = std::make_shared<Objects::Player::Player>(Vec2(-20, level.PlayerStartPosition.Y));

			//If this is false we must have loaded a save file, so don't run in from the left.
			if (ThePlayer->GetPosition().X <= level.PlayerStartPosition.X + 2)
			{
				//If the LEVEL_NO_PLAYER_INTRO_FLAG is set, just spawn the player at the given location rather than having them run onto the screen from the left.
				if (!level.Flags.contains(LEVEL_NO_PLAYER_INTRO_FLAG))
				{
					ThePlayer->QueueTargetEvent(Objects::Player::Player::TargetEvent(level.PlayerStartPosition, true, true, 0.6));
				}
				else {
					ThePlayer->SetPosition({ level.PlayerStartPosition.X, level.PlayerStartPosition.Y });
				}
			}

			Rendering::Renderer::LoadActiveObject(ThePlayer.get(), 2); //Spawn in the player on Active Layer 2.
		}

		//TEST
		//MusicSync::MusicSync::SetCurrentSong(134, 2);

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

		//Generate clouds if there are any to be generated.
		Environment::CloudGenerator::GenerateClouds();
		
		//CHNAGE TO DETECT WHAT LEVEL IS BEING LOADED AND CALL THE APPROPRIATE FUNCTION.
		//Objects::Environment::Levels::Town1Manager::InitLevel();

		m_currentLevelSystem = nullptr;
		switch (level.ID.World)
		{
		case 0:
			{
				switch (level.ID.Level)
				{
				case 0:
					//Main Menu
					m_currentLevelSystem = std::unique_ptr<LevelSystem>(new MainMenuManager());
					break;
				}
				break;
			}
		case 1:
			{
				switch (level.ID.Level)
				{
				case 0:
					//Introduction.
					m_currentLevelSystem = std::unique_ptr<LevelSystem>(new IntroductionLevelManager());
					break;
				}
				break;
			}
		}


		//TODO: Add a check on weather the current level uses lighting or not.
		//Rendering::Lighting::SimpleLightingManager::EnableLighting(DEFAULT_LEVEL_SIZE_X/10, true);

		//Rendering::Lighting::SimpleLightingManager::RegisterSource(new Lighting::LightingSource({ 150.f, 27.f }, 50.f, 25.f, Lighting::POINT_LIGHT, true, true), true);

		//Rendering::Lighting::SimpleLightingManager::RegisterSource(new Lighting::LightingSource(Vec2(200, 21), -100.f, -10.f, Lighting::POINT_LIGHT));

	/*	
	----------------------------PARTICLE TEST----------------------------
	GameObject* leaf = Instantiate::LevelObjectHandler::GetLevelObject("leaf_particle_objects", "leaf_1");
		leaf->SetPosition(Vec2(0,0));

		{
		using namespace Particles;

			ParticleEmitter* testPE = new ParticleEmitter(ThePlayer->GetPosition());
			Particle testP = leaf;

			testP.Velocity = Vec2(3.f, 1.f);

			testPE->RegisterParticle(testP);

			Renderer::LoadActiveObject(testPE);

			testPE->SpawnParticles(15);
		
		}

		*/

		/*
		----------------------------ENEMY TEST----------------------------
		Enemies::LeftRightEnemy::LeftRightEnemyAttributes* attributes = new Enemies::LeftRightEnemy::LeftRightEnemyAttributes();
		attributes->EndpointPause = 2.F;
		attributes->MovementSpeed = 2.F;
		attributes->TerminalMovementSpeed = 40.F;
		Enemies::LeftRightEnemy* lreTest = new Enemies::LeftRightEnemy({ 100, 21 }, { 32, 32 }, Renderer::GetSprite(2), { 100, -1 }, { 200, -1 }, attributes);
		
	
		Renderer::LoadActiveObject(lreTest);*/

		//Create a sound and set it to loop.
		//Audio::AudioVoice testMusic = Audio::SoundManager::Play(1, Audio::SoundManager::MusicGroup);
		//Audio::SoundManager::GetAudioPlayer()->setLooping(testMusic, true);

		//Pause the current background music.
		//Audio::SoundManager::GetAudioPlayer()->setPause(level.CurrentBGMusic, true);

		//testAudioObject = new GameObject(level.PlayerStartPosition, { 32, 32 }, Rendering::Renderer::GetSprite(SpriteBase(54)));
		//Rendering::Renderer::LoadActiveObject(testAudioObject);


		//Environment::Buildings::Door* testDoor = new Environment::Buildings::Door({ 125, 21 }, { 3, 28 }, Renderer::GetSprite(61), Renderer::GetSprite(59));
		//Rendering::Renderer::LoadActiveObject(testDoor);

		//Environment::Buildings::FrontWall* frontWall = new Environment::Buildings::FrontWall({ 200, 21 }, { 32, 32 }, Renderer::GetSprite(58));
		//Rendering::Renderer::LoadActiveObject(frontWall);

		//MusicSync::MusicSync::SetCurrentSong(80, 4);

		//MusicSync::MusicSync::Subscribe(testAudioUpdate);

		//TODO: add music sync to everything.

		//GameObject* test = new GameObject({ 400, 50 }, { 25 }, Renderer::GetSprite(24));
		//Renderer::LoadActiveObject(test);

		/*std::shared_ptr<Cutscenes::DialogueSequence> opt1(new Cutscenes::DialogueSequence(1, Cutscenes::DialogueSequence::DialogueEvent("Thanks, it will be great!", nullptr)));
		std::shared_ptr<Cutscenes::DialogueSequence> opt2(new Cutscenes::DialogueSequence(1, Cutscenes::DialogueSequence::DialogueEvent("Wow you suck.", nullptr)));

		Cutscenes::DialogueSequence mainSequence(2,
			Cutscenes::DialogueSequence::DialogueEvent("Hey! You look like you need\nsome cash... Check out my Pyramid Scheme!!", test, 1.f),
			Cutscenes::DialogueSequence::DialogueEvent("That is Awesome!/Freak no!", test, 1.f, 2, opt1, opt2)
		);
		
		

		Cutscenes::DialogueManager::INSTANCE->PlayDialogueSequence(mainSequence);*/

		//Testing Glitch Area
		//GlitchedRegion* gr = new GlitchedRegion(Vec2(80, 0), Vec2(300, 100));
		//Renderer::LoadObject(gr, 2, false);
		
		//Test Chest
		//Renderer::LoadObject(new GAME_NAME::Items::Inventories::InventoryContainer("Test Chest", 10, { 100, 21 }, { 12, 8 }, Renderer::GetSprite(19), 0), 2);

	}

	void TestGame::TogglePauseState()
	{
		if (SettingsManager::SettingsMenuIsOpen()) { return; }
		
		//Close any open inventory.
		Items::Inventories::InventoryContainer* currentInv = Items::Inventories::InventoryContainerRenderer::GetCurrentContainer();
		if (currentInv != nullptr)
		{
			currentInv->CloseGUI();

			return;
		}

		m_gamePaused = !m_gamePaused;
		
		if (m_gamePaused)
		{
			if (GUI::GUIManager::PreventMenus)
			{
				m_gamePaused = false;
				return;
			}

			GUI::GUIManager::PreventMenus = true;

			pauseMenu_buttonIdOffset = GUI::Menus::GUIMenu::LoadMenu("/pause", new std::function(pauseMenu_guiCallback));

			//Prevent object updating to PAUSE GAME and PHYSICS.
			Rendering::Renderer::UpdateObjects = false;

			//Create text objects.
			m_pauseMenuObjects = Text::TextRenderer::RenderWord("resume", { 25, 68 }, 12.f, 0.f, 2);
			auto renderedWordSettings = Text::TextRenderer::RenderWord("settings", { 25, 48 }, 12.f, 0.f, 2);
			auto renderedWordQuit = Text::TextRenderer::RenderWord("quit", { 25, 28 }, 12.f, 0.f, 2);
			m_pauseMenuObjects.insert(m_pauseMenuObjects.end(), renderedWordQuit.begin(), renderedWordQuit.end());
			m_pauseMenuObjects.insert(m_pauseMenuObjects.end(), renderedWordSettings.begin(), renderedWordSettings.end());

		}
		else {
			GUI::GUIManager::PreventMenus = false;

			GUI::Menus::GUIMenu::RemoveLastMenu();

			//Renable all objects to RESUME GAME and PHYSICS.
			Rendering::Renderer::UpdateObjects = true;

			for (GUI::StaticGUIElement* obj : m_pauseMenuObjects)
			{
				Renderer::UnloadGUIElement(obj, 2);
				//delete obj;
			}

			m_pauseMenuObjects.clear();
		}
	}

	void TestGame::LoadLevelAndAllData(const char* levelPath)
	{
		Game_nextLevelToLoad = std::string(levelPath);
	}

	void TestGame::LoadLevelOnlyObjects(const char* levelPath, Vec2 newPlayerPos)
	{
		LoadLevelAndAllData(levelPath);
		Game_nextLevelIsOnlyObjects = true;
		Game_playerNewPos = newPlayerPos;
	}

}