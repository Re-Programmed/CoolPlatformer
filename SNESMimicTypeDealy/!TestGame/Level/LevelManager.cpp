#include "LevelManager.h"
#include "../TestGame.h"
#include "../Mappings.h"

#include "../../Utils/Math/VMath.h"

#define CIRCLE_WIPE_TEXTURE SpriteBase(190)

constexpr int CIRCLE_WIPE_DURATION = 1;

namespace GAME_NAME::Level
{
	bool LevelManager::CircleAnimationWasCompleted = false;
	std::mutex LevelManager::CircleAnimationWasCompletedLock;

	void LevelManager::LoadPlayerHouse()
	{
		//TestGame::INSTANCE->LoadLevel("/player_house_1_1", TestGame::LEVEL_DATA_TEXTURES_BACKGROUND);

		TestGame::INSTANCE->LoadLevel("/global_assets", TestGame::LEVEL_DATA_TEXTURES_SPRITES);

		TestGame::INSTANCE->LoadLevel("/player_house_1_1", (GAME_NAME::Game::Game::LEVEL_DATA)(TestGame::LEVEL_DATA_TEXTURES_BACKGROUND xor TestGame::LEVEL_DATA_ALL));

		GAME_NAME::Mappings::LoadObjectsWithDefaultMapping("/player_house_1_1");
		TestGame::INSTANCE->RenderFront = true;
	}

	void LevelManager::LoadLevelData(const char* levelPath, bool renderFront)
	{
		/*TestGame::INSTANCE->ClearLevel(TestGame::LEVEL_DATA_ALL);
		Renderer::ClearGUIObjects(0, 0);
		Renderer::ClearGUIObjects(0, 1);
		Renderer::ClearGUIObjects(0, 2);
		Renderer::ClearObjects();
		Renderer::ClearTextures();

		TestGame::INSTANCE->RenderFront = renderFront;
		TestGame::INSTANCE->LoadLevel(levelPath, TestGame::LEVEL_DATA_TEXTURES_BACKGROUND);
		TestGame::INSTANCE->LoadLevel("/global_assets", TestGame::LEVEL_DATA_TEXTURES_SPRITES);
		TestGame::INSTANCE->LoadLevel(levelPath, (GAME_NAME::Game::Game::LEVEL_DATA)(TestGame::LEVEL_DATA_TEXTURES_BACKGROUND xor TestGame::LEVEL_DATA_ALL));
		GAME_NAME::Mappings::LoadObjectsWithDefaultMapping(levelPath);*/

		TestGame::INSTANCE->LoadLevelAndAllData(levelPath);

		dynamic_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->UnlockCamera();
	}

	void LevelManager::LevelCircleAnimation(Vec2 targetPosition, bool reverse, bool removeGraphicsWhenDone)
	{
		SetCircleAnimationCompleted(false);

		if (targetPosition.X < 1 && targetPosition.Y < 1) {
			targetPosition = Vec2{ TargetResolutionX / 2.f, TargetResolutionY / 2.f };
		}

		Vec2 screenCoords = targetPosition * 2.f;
		Vec2 scale = Vec2{ TargetResolutionX, TargetResolutionY } * 9.f;

		auto s = Renderer::GetSprite(CIRCLE_WIPE_TEXTURE);

		StaticGUIElement* wipeCircle = new StaticGUIElement(((screenCoords - scale) / 2), scale, s->GetSpriteId());
		Renderer::LoadGUIElement(wipeCircle, 2);

		std::array<StaticGUIElement*, 4> borderSquares;

		borderSquares[0] = new StaticGUIElement(Vec2{ TargetResolutionX + 15.f, TargetResolutionY + 15.f }, { wipeCircle->GetScale().X * 4.f, wipeCircle->GetScale().Y }, s->GetSpriteId());
		borderSquares[1] = new StaticGUIElement(Vec2{ TargetResolutionX + 15.f, TargetResolutionY + 15.f }, { wipeCircle->GetScale().X * 4.f, wipeCircle->GetScale().Y }, s->GetSpriteId());
		borderSquares[2] = new StaticGUIElement(Vec2{ TargetResolutionX + 15.f, TargetResolutionY + 15.f }, { wipeCircle->GetScale().X, wipeCircle->GetScale().Y * 4.f }, s->GetSpriteId());
		borderSquares[3] = new StaticGUIElement(Vec2{ TargetResolutionX + 15.f, TargetResolutionY + 15.f }, { wipeCircle->GetScale().X, wipeCircle->GetScale().Y * 4.f }, s->GetSpriteId());

		Renderer::LoadGUIElement(borderSquares[0], 2);
		Renderer::LoadGUIElement(borderSquares[1], 2);
		Renderer::LoadGUIElement(borderSquares[2], 2);
		Renderer::LoadGUIElement(borderSquares[3], 2);

		std::thread animation([wipeCircle, targetPosition, reverse, removeGraphicsWhenDone](std::array<StaticGUIElement*, 4> borderSquares) {
			Vec2 screenCoords = { targetPosition.X * 2.f, targetPosition.Y * 2.f };

			float initScale = wipeCircle->GetScale().X;
			double lerpPortion = 0;

			for (int i = 0; i < 300; i++)
			{
				Vec2 scale = wipeCircle->GetScale();

				std::this_thread::sleep_for(std::chrono::milliseconds(CIRCLE_WIPE_DURATION));
				
				//-cos(p*i/600))^2+1
				lerpPortion = -(std::pow(std::cos(M_PIf * i / 600.0), 2)) + 1;

				if (reverse)
				{
					lerpPortion = 1 - lerpPortion;
				}

				std::cout << lerpPortion << std::endl;

				scale.X = std::lerp(initScale, 0.f, lerpPortion);
				scale.Y = scale.X;

				wipeCircle->SetScale(scale);
				wipeCircle->SetPosition(((screenCoords - scale) / 2));


				borderSquares[0]->SetPosition(wipeCircle->GetPosition() - (wipeCircle->GetScale() * Vec2 { 0.f, -1.f }) - Vec2{ initScale, 0.f } - Vec2{ 0.f, std::clamp(125.f - static_cast<float>(i), 1.f, 125.f) });

				borderSquares[1]->SetPosition(wipeCircle->GetPosition() - (borderSquares[1]->GetScale() * Vec2 { 0.f, 1.f }) - Vec2{ initScale, 0.f } + Vec2{ 0.f, std::clamp(125.f - static_cast<float>(i), 1.f, 125.f) });
				
				borderSquares[2]->SetPosition(wipeCircle->GetPosition() + (Vec2 { wipeCircle->GetScale().X, 0.f}) - Vec2{std::clamp(125.f - static_cast<float>(i), 1.f, 125.f), 0.f});
								
				Vec2 pos = wipeCircle->GetPosition() - (Vec2 { initScale, 0.f }) + Vec2{ std::clamp(125.f - static_cast<float>(i), 1.f, 125.f), 0.f};
				borderSquares[3]->SetPosition(pos);
			}

			if (removeGraphicsWhenDone)
			{
				Renderer::UnloadGUIElement(wipeCircle, 2);

				Renderer::UnloadGUIElement(borderSquares[0], 2);
				Renderer::UnloadGUIElement(borderSquares[1], 2);
				Renderer::UnloadGUIElement(borderSquares[2], 2);
				Renderer::UnloadGUIElement(borderSquares[3], 2);

				delete wipeCircle;
				delete borderSquares[0];
				delete borderSquares[1];
				delete borderSquares[2];
				delete borderSquares[3];

			}

			SetCircleAnimationCompleted(true);


		}, borderSquares);

		animation.detach();

	}

}

