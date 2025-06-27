#pragma once

#include "../../Utils/Math/Vec2.h"
#include "../../Rendering/Sprite.h"

#include <mutex>

namespace GAME_NAME::Level
{
	class LevelManager
	{
	public:
		static void LoadPlayerHouse();

		static void LoadLevelData(const char* levelPath, bool renderFront = true);
		 
		static void LevelCircleAnimation(GAME_NAME::MathUtils::Vec2 targetPosition, bool reverse = false, bool removeGraphicsWhenDone = true);


		inline static void SetCircleAnimationCompleted(bool val)
		{
			LevelManager::CircleAnimationWasCompletedLock.lock();
			LevelManager::CircleAnimationWasCompleted = val;
			LevelManager::CircleAnimationWasCompletedLock.unlock();
		}

		inline static bool GetCircleAnimationCompleted()
		{
			return CircleAnimationWasCompleted;
		}
	private:
		static bool CircleAnimationWasCompleted;
		static std::mutex CircleAnimationWasCompletedLock;
	};
};