#pragma once
#include "../Audio/MusicManager.h"

namespace GAME_NAME
{
	namespace Game
	{
		typedef struct Level
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
		};
	}
}