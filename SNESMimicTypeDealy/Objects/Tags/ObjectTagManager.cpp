#include "ObjectTagManager.h"

namespace GAME_NAME::Objects::Tags
{
	std::multimap<std::string, GameObject*> ObjectTagManager::m_taggedObjects;

	std::pair<std::multimap<std::string, GameObject*>::const_iterator, std::multimap<std::string, GameObject*>::const_iterator> ObjectTagManager::GetObjectsWithTag(std::string tag)
	{
		return m_taggedObjects.equal_range(tag);
	}

}
