#pragma once
#include <soloud.h>
#include <vector>

namespace GAME_NAME
{
	namespace Audio
	{
		typedef SoLoud::Soloud AudioPlayer;
		typedef SoLoud::handle AudioGroup;
		typedef SoLoud::handle AudioVoice;
		typedef SoLoud::AudioSource AudioSource;

		static class MusicManager
		{
		public:
			static void Init();
			static void DeInit();

			static AudioPlayer* GetAudioPlayer();

			static void RegisterAudioSource(AudioSource* source);

			static AudioSource* GetAudioSource(int index);

			static void ClearSources();

			static AudioVoice Play(int index, float volume = -1.0F, float pan = 0.0F, bool paused = false, unsigned int bus = 0U);
		private: 
			static std::vector<AudioSource*> m_sources;

			static AudioPlayer* m_audioPlayer;

			static AudioGroup m_musicGroup;
			static AudioGroup m_sfxGroup;
		};
	}
}