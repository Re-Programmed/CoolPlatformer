#pragma once

#include "../GameObject.h"
#include <map>

namespace GAME_NAME::Objects::Tags
{
	class ObjectTagManager
	{
	public:
		static std::pair<std::multimap<std::string, GameObject*>::const_iterator, std::multimap<std::string, GameObject*>::const_iterator> GetObjectsWithTag(std::string tag);

		static inline void TagObject(GameObject* object, std::string tag)
		{
			m_taggedObjects.emplace(tag, object);
		}

		static inline void ClearTaggedObjects()
		{
			m_taggedObjects.clear();
		}

	private:
		static std::multimap<std::string, GameObject*> m_taggedObjects;
	};
}