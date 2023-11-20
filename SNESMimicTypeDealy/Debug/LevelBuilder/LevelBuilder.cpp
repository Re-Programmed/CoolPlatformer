#if _DEBUG

#include "LevelBuilder.h"
#include "../../Resources/AssetManager.h"
#include "../../Input/InputManager.h"
#include "../../!TestGame/TestGame.h"
#include "../../Rendering/DynamicSprite.h"
#include "../../Objects/GUI/GUIButton.h"
#include "../../Objects/GUI/GUIManager.h"
#include "SpawnObjects.h"

//The area around the mouse that can be used to select objects.
constexpr unsigned int MouseSelectionRadius = 100U;

namespace GAME_NAME::Debug::LevelBuilder
{
	LevelBuilder* LevelBuilder::m_currentLevelBuilder;
	bool LevelBuilder::m_objectMenuOpen = false;

	const Vec4 RedTextureColor[4] = {
		Vec4(1, 0, 0, 1),
		Vec4(1, 0, 0, 1),
		Vec4(1, 0, 0, 1),
		Vec4(1, 0, 0, 1)
	};

	void LevelBuilder::InitLevelBuilderAssets(GAME_NAME::Game::Game* game)
	{
		//Load level editor textures.
		game->LoadLevel("/debug_level_builder_assets", Game::Game::LEVEL_DATA_TEXTURES_SPRITES);
	}

	void LevelBuilder::InitLevelBuilder(GAME_NAME::Game::Game* game)
	{
		//game->LoadLevel("/town_1", Game::Game::LEVEL_DATA_TEXTURES_BACKGROUND, true);
		//game->LoadLevel("/global_assets", Game::Game::LEVEL_DATA_TEXTURES_SPRITES);
		//game->LoadLevel("/town_1", (GAME_NAME::Game::Game::LEVEL_DATA)(Game::Game::LEVEL_DATA_ALL xor Game::Game::LEVEL_DATA_TEXTURES_BACKGROUND));

		const int spriteCount = Renderer::GetSpriteCount() + Renderer::GetBackgroundSpriteCount();

		//Create a new loaded level builder.
		m_objectMenuOpen = false;
		new LevelBuilder(game, spriteCount);
	}

	void LevelBuilder::Render()
	{
		if (m_currentLevelBuilder == nullptr) { return; }

		DrawObjectMenu();

		DynamicSprite dsobj = DynamicSprite(61);
		dsobj.Render(m_currentLevelBuilder->m_currentGame->GetCamera()->GetPosition(), InputManager::GetMouseWorldPosition(m_currentLevelBuilder->m_currentGame->GetCamera()) - Vec2(MouseSelectionRadius / 2), Vec2(MouseSelectionRadius));

		if (m_currentLevelBuilder->m_editObject != nullptr)
		{
			//Render selected object.
			DynamicSprite ds = DynamicSprite(m_currentLevelBuilder->m_editObject->GetSprite()->GetSpriteId());
			ds.UpdateTextureColor(RedTextureColor);
			ds.Render(m_currentLevelBuilder->m_currentGame->GetCamera()->GetPosition(), m_currentLevelBuilder->m_editObject->GetPosition() + m_currentLevelBuilder->m_editObject->GetScale(), m_currentLevelBuilder->m_editObject->GetScale(), m_currentLevelBuilder->m_editObject->GetRotation() + 180.f);
		}

	}

	void LevelBuilder::DrawObjectMenu()
	{
		DynamicSprite* ds = Renderer::GetDynamicSprite(SpriteBase(-1));
		Rendering::Camera::Camera* c = m_currentLevelBuilder->m_currentGame->GetCamera();
		ds->Render(c->GetPosition(), c->UIToGlobal(Vec2(0, 0)), Vec2(TargetResolutionX/5.5, TargetResolutionY));
		delete ds;

using namespace GUI;

		if (m_objectMenuOpen)
		{
			return;
		}

		m_objectMenuOpen = true;
		for (int i = 0; i < LVLBUILDER_SPAWNABLE_COUNT; i++)
		{
			SpawnObjects::Spawnable sObj = SpawnObjects::GetSpawnable(i);

			int buttonData[1]{i};
			GUIButton* btn = new GUIButton(Vec2(0, 0), Vec2(30, 30), sObj.MyObject->GetSprite()->GetSpriteId(), [](int spawnable) {
				SpawnObjects::Spawnable obj = SpawnObjects::GetSpawnable(spawnable);
				obj.MyObject->SetPosition(TestGame::ThePlayer->GetPosition());
				Renderer::InstantiateObject(obj);

				std::cout << "Spawning object: " << spawnable << ", at: " << obj.MyObject->GetPosition().ToString() << std::endl;
				}, i);

			Renderer::LoadGUIElement(btn);
			GUIManager::RegisterButton(btn);
		}
	}

	bool PerformedButtonClickEvent = false;
	void LevelBuilder::Update(GLFWwindow* window)
	{

		if (InputManager::GetMouseButton(0))
		{
			if (PerformedButtonClickEvent == false)
			{
				PerformedButtonClickEvent = true;
				GUI::GUIManager::ButtonClickEvent(InputManager::GetMouseScreenPosition());
			}
		}
		else {
			PerformedButtonClickEvent = false;
		}

		if (m_editObject != nullptr)
		{
			if (InputManager::GetKey(DEBUG_SET_OBJECT_X))
			{

			}
		}


		if (InputManager::GetMouseButton(1))
		{
			if (m_interactKeyDown)
			{
				return;
			}

			m_interactKeyDown = true;

			Vec2 cPos = InputManager::GetMouseWorldPosition(TestGame::INSTANCE->GetCamera());

			GameObject* closestObj = nullptr;
			float shortestDist = 100.f;

			std::vector<GameObject*> objs = Renderer::GetAllObjectsInArea(cPos - Vec2(MouseSelectionRadius/2), Vec2(MouseSelectionRadius));

			int c = 0;
			for (GameObject* obj : objs)
			{
				const float d = Vec2::Distance(obj->GetPosition(), cPos);
				if (d < shortestDist && m_editObject != obj)
				{
					closestObj = obj;
					shortestDist = d;
				}
				c++;
			}

			std::cout << "Found " << c << " objects." << std::endl;

			if (closestObj != nullptr)
			{
				m_editObject = closestObj;
			}
		}
		else {
			m_interactKeyDown = false;
		}
	}


	void LevelBuilder::DestroyLevelBuilder()
	{

		if (m_currentLevelBuilder != nullptr)
		{
			UpdateManager::RemoveUpdateable(m_currentLevelBuilder->m_updateIndex);

			delete m_currentLevelBuilder;
		}
	}
}

#endif
