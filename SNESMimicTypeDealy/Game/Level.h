#pragma once
#include "../Audio/SoundManager.h"
#include "../Utils/Math/Vec2.h"

namespace GAME_NAME
{
	namespace Game
	{
		using namespace MathUtils;

		typedef struct Level	//Stores basic data about levels.
		{
			/// <summary>
			/// Name of the level.
			/// </summary>
			std::string Name;
			/// <summary>
			/// World and level ID.
			/// </summary>
			struct { char World, Level; } ID;

			/// <summary>
			/// The voice of the current background track.
			/// </summary>
			Audio::AudioVoice CurrentBGMusic;

			Vec2 PlayerStartPosition = Vec2::Zero;
		};
	}
}