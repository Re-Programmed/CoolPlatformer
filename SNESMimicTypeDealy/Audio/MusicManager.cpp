#include "MusicManager.h"
#if _DEBUG
#include "../Debug/DebugLog.h"
#endif
namespace GAME_NAME
{
	namespace Audio
	{
		AudioPlayer* MusicManager::m_audioPlayer;
		AudioGroup MusicManager::m_musicGroup;
		AudioGroup MusicManager::m_sfxGroup;

		std::vector<AudioSource*> MusicManager::m_sources;

		void MusicManager::Init()
		{
			m_audioPlayer = new AudioPlayer();

#if _DEBUG
			DEBUG::DebugLog::Log("[MUSIC] Initilized MusicManager.");
#endif
			m_audioPlayer->init();

			m_sfxGroup = m_audioPlayer->createVoiceGroup();
			m_musicGroup = m_audioPlayer->createVoiceGroup();
		}

		void MusicManager::DeInit()
		{
#if _DEBUG
			DEBUG::DebugLog::Log("[MUSIC] De-Initilized MusicManager.");
#endif
			m_audioPlayer->deinit();
			delete m_audioPlayer;
		}


		AudioPlayer* MusicManager::GetAudioPlayer()
		{
			return m_audioPlayer;
		}

		void MusicManager::RegisterAudioSource(AudioSource* source)
		{
			m_sources.push_back(source);
		}

		AudioSource* MusicManager::GetAudioSource(int index)
		{
			return m_sources[index];
		}

		void MusicManager::ClearSources()
		{
			m_sources.clear();
		}

		AudioVoice MusicManager::Play(int index, float volume, float pan, bool paused, unsigned int bus)
		{
			return m_audioPlayer->play(*GetAudioSource(index), volume, pan, paused, bus);
		}
	}
}