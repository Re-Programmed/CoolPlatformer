#pragma once
#include <vector>

namespace GAME_NAME
{
	namespace MusicSync
	{
		class MusicSync
		{
		public:
			typedef struct SongPosition {
				uint8_t sp_measure;												//Current measure of the song.
				char sp_beat;													//Current beat of the current measure.
			};

			static void Subscribe(void func(SongPosition songPosition));		//Subscribes a function to be updated each beat of the current song.

			static void Update();							//Updates. Should be called every frame.

			/// <summary>
			/// Sets the current beats per second.
			/// </summary>
			/// <param name="BPS">Beats Per Second</param>
			static inline void SetBPS(double BPS)
			{
				m_SPB = 1.0/BPS;
			}

			/// <summary>
			/// Sets the current beats per minute.
			/// </summary>
			/// <param name="BPS">Beats Per Minute</param>
			static inline void SetBPM(double BPM)
			{
				SetBPS(BPM / 60.0);
			}
			
			/// <summary>
			/// Get seconds per beat.
			/// </summary>
			/// <returns>Seconds Per Beat</returns>
			static inline double GetSPB()
			{
				return m_SPB;
			}

			/// <summary>
			/// Returns the fraction of time elapsed between the beat for every value of beats and the next beat.
			/// </summary>
			/// <returns></returns>
			static inline double GetElapsedTimeWithinBeats(int beats)
			{
				if (m_SPB == 0 || beats == 0) { return 0; }
				return (m_beatCounter / m_SPB + (m_currentBeat % beats))/beats;
			}

			/// <summary>
			/// Get beats per measure.
			/// </summary>
			/// <returns>Beats Per Measure</returns>
			static inline char GetBPMeasure()
			{
				return m_BPMeasure;
			}

			/// <summary>
			/// Sets the beats per measure.
			/// </summary>
			/// <param name="BPMeasure">Beats Per Measure</param>
			static inline void SetBPMeasure(char BPMeasure)
			{
				m_BPMeasure = BPMeasure;
			}

			/// <summary>
			/// Gets the current SongPosition.
			/// </summary>
			/// <returns>Current SongPosition</returns>
			static inline SongPosition GetSongPosition()
			{
				return m_songPosition;
			}

			/// <summary>
			/// Sets the BPM and BPMeasure while resetting the current song position.
			/// </summary>
			/// <param name="BPM">Beats Per Minute (Tempo)</param>
			/// <param name="BPMeasure">Beats Per Measure (Time Signature)</param>
			static inline void SetCurrentSong(double BPM, char BPMeasure)
			{
				SetBPM(BPM);
				SetBPMeasure(BPMeasure);

				m_songPosition.sp_beat = 0;
				m_songPosition.sp_measure = 0;
				m_currentBeat = 0;
			}
		private:
			static std::vector<void(*)(SongPosition songPosition)> m_subscribers;	//Functions to be updated each frame.
			static double m_beatCounter;							//Elapsed time since last beat.

			static double m_SPB;									//Seconds Per Beat
			static char m_BPMeasure;								//Beats Per Measure

			static short int m_currentBeat;							//Total current beats that have occured the song.

			static SongPosition m_songPosition;						//Current position in the current song.
		};
	}
}