#pragma once
#include <soloud.h>
#include <soloud_wavstream.h>

namespace GAME_NAME
{
	namespace Audio
	{
		class Sound		//Stores a WAV file for SoundManager.
			: public SoLoud::WavStream
		{
		public:
			Sound(const char* file);	//Takes in a path to a file.
		};
	}
}