#include "CollectableTracker.h"

#include <sstream>

namespace GAME_NAME::Objects::Collectables
{
	CollectableTracker::CollectableData* const CollectableTracker::CurrentCollectableData = new CollectableTracker::CollectableData();

	void CollectableTracker::CollectableData::Decode(const SaveParam params)
	{
		std::stringstream paramsIterator(params);
		std::string param;

		int lastKey = 0;
		while (std::getline(paramsIterator, param, ':'))
		{
			if (lastKey != 0)
			{
				CollectionData.emplace(std::make_pair(lastKey, std::stoi(param)));
				lastKey = 0;
				continue;
			}

			lastKey = std::stoi(param);
		}
	}

	CollectableTracker::CollectableData::SaveParam CollectableTracker::CollectableData::Encode()
	{
		SaveParam result;

		for (auto collectable : this->CollectionData)
		{
			result.append(std::to_string(collectable.first));
			result.append(":");
			result.append(std::to_string(collectable.second));
			result.append(":");
		}

		return result;
	}


	void CollectableTracker::AddCollectable(COLLECTABLE_TYPE type)
	{
		int previous = (CurrentCollectableData->CollectionData.contains(type) ? CurrentCollectableData->CollectionData.at(type) : 0);

		CurrentCollectableData->CollectionData.emplace(std::make_pair((int)type, previous + 1));
	}

}

