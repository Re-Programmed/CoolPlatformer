#include "UpdateManager.h"
#include "Time/GameTime.h"

namespace GAME_NAME
{
	namespace Utils
	{
		std::vector<IUpdateable*> UpdateManager::m_updateables {
			new Time::GameTime()
		};


		void UpdateManager::Update(GLFWwindow* window)
		{
			for (IUpdateable* u : m_updateables)
			{
				u->Update(window);
			}

		}

		int UpdateManager::RegisterUpdateable(IUpdateable* updateable)
		{
			m_updateables.push_back(updateable);
			return m_updateables.size() - 1;
		}

		void UpdateManager::RemoveUpdateable(UpdateIndex index)
		{
			m_updateables.erase(m_updateables.begin() + index);
		}
	}
}