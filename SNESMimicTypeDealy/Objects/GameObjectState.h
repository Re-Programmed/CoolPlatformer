#pragma once

#include <string>

namespace GAME_NAME
{

	namespace Objects
	{
		class GameObjectState
		{
		public:
			GameObjectState(std::string objectSaveID)
				: m_objectSaveID(objectSaveID)
			{
				//LoadState();
			}

			virtual void LoadState() = 0;
			
			virtual void SaveState() = 0;

			inline void SetToBeSaved(bool toBeSaved)
			{
				m_toBeSaved = toBeSaved;
			}
		protected:
			const std::string m_objectSaveID;
			bool m_toBeSaved = false;
		};
	}
}