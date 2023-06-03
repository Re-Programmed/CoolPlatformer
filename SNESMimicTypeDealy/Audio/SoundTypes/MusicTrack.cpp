#include "MusicTrack.h"

namespace GAME_NAME
{
	namespace Audio
	{
		MusicTrack::MusicTrack(const char* file)
			: SoLoud::WavStream()
		{
			this->load(file);
		}

	}
}