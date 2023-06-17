#include "Sound.h"

namespace GAME_NAME
{
	namespace Audio
	{
		Sound::Sound(const char* file)
			: SoLoud::WavStream()
		{
			this->load(file);
		}

	}
}