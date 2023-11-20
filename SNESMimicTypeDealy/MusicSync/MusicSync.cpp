#include "MusicSync.h"
#include "../Utils/Time/GameTime.h"
#include <thread>
#include "../Settings/SettingsGlobals.h"

namespace GAME_NAME
{
	namespace MusicSync
	{
		std::vector<void(*)(MusicSync::SongPosition songPosition)> MusicSync::m_subscribers;

		double MusicSync::m_beatCounter;
		char MusicSync::m_BPMeasure;
		MusicSync::SongPosition MusicSync::m_songPosition;
		double MusicSync::m_SPB;

		short int MusicSync::m_currentBeat;

		void MusicSync::Subscribe(void func(MusicSync::SongPosition songPosition))
		{
			m_subscribers.push_back(func);
		}

		void MusicSync::Update()
		{
			m_beatCounter += Utils::Time::GameTime::DeltaTime::GetDeltaTime();

			if (m_beatCounter >= m_SPB)	//The amount of seconds in 1 beat has passed.
			{
				m_songPosition.sp_beat++;	//Increment the current beat.
				m_currentBeat++;

				if (m_songPosition.sp_beat == m_BPMeasure)	//If we have just reached the beat equal to the number of beats in a measure increment the measure.
				{
					m_songPosition.sp_beat = 0;
					m_songPosition.sp_measure++;
				}

				//Call all subscribers in threads while observing the max threads:
				std::vector<std::thread> beatTicks;

				for (auto &func : m_subscribers)
				{
					beatTicks.push_back(std::thread(func, m_songPosition));

					if (beatTicks.size() >= AppData::Settings::SettingsGlobals::MaxThreads.Value)
					{
						for (auto& thread : beatTicks)
						{
							if (thread.joinable())
							{
								thread.join();
							}
						}

						beatTicks.clear();
					}
				}

				for (auto& thread : beatTicks)
				{
					if (thread.joinable())
					{
						thread.join();
					}
				}

				m_beatCounter = 0;
			}
		}
	}

}