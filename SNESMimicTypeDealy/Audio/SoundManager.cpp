#include "SoundManager.h"
#if _DEBUG
#include "../Debug/DebugLog.h"
#endif
namespace GAME_NAME
{
	namespace Audio
	{
		AudioPlayer* SoundManager::m_audioPlayer;
		AudioGroup SoundManager::MusicGroup;
		AudioGroup SoundManager::SFXGroup;

		std::vector<std::shared_ptr<AudioSource>> SoundManager::m_sources;

		AudioVoice SoundManager::BGMusic;
		AudioVoice SoundManager::WaterMusic;

		void SoundManager::Init()
		{
			m_audioPlayer = new AudioPlayer();

#if _DEBUG
			DEBUG::DebugLog::Log("[MUSIC] Initilized MusicManager.");
#endif
			m_audioPlayer->init();

			SFXGroup = m_audioPlayer->createVoiceGroup();
			MusicGroup = m_audioPlayer->createVoiceGroup();
		}

		void SoundManager::DeInit()
		{
#if _DEBUG
			DEBUG::DebugLog::Log("[MUSIC] De-Initilized MusicManager.");
#endif
			m_audioPlayer->deinit();
			//delete m_audioPlayer;
		}


		

		void SoundManager::RegisterAudioSource(std::shared_ptr<AudioSource> source)
		{
			m_sources.push_back(source);
		}

		std::shared_ptr<AudioSource> SoundManager::GetAudioSource(int index)
		{
			return m_sources[index];
		}

		void SoundManager::ClearSources()
		{
			for (std::shared_ptr<AudioSource> as : m_sources)
			{
				as->stop();
			}

			m_sources.clear();
		}

		AudioVoice SoundManager::Play(int index, AudioGroup group, float volume, float pan, bool paused, unsigned int bus)
		{
			AudioVoice aVoice = m_audioPlayer->play(*GetAudioSource(index), volume, pan, true, bus);
			m_audioPlayer->addVoiceToGroup(group, aVoice);

			if (!paused)
			{
				m_audioPlayer->setPause(aVoice, false);
			}

			return aVoice;
		}

	}
}