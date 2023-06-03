#pragma once
#include <soloud.h>
#include <soloud_wavstream.h>
#include "../MusicManager.h"

namespace GAME_NAME
{
	namespace Audio
	{
		class MusicTrack
			: public SoLoud::WavStream
		{
		public:
			MusicTrack(const char* file);
		};
	}
}