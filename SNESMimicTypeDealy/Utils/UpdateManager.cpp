#include "UpdateManager.h"
#include "Time/GameTime.h"
#include "../Components/Physics/Collision/CollisionManager.h"

namespace GAME_NAME
{
	namespace Utils
	{
		std::vector<IUpdateable*> UpdateManager::m_updateables{
			new Time::GameTime()
		};


		void UpdateManager::Update(GLFWwindow* window)
		{
			for (IUpdateable* u : m_updateables)
			{
				u->Update(window);
			}

		}

		UpdateIndex UpdateManager::RegisterUpdateable(IUpdateable* updateable)
		{
			m_updateables.push_back(updateable);
			return m_updateables.size() - 1;
		}

		void UpdateManager::RemoveUpdateable(const UpdateIndex index)
		{
			m_updateables.erase(m_updateables.begin() + index);
		}
	}
}