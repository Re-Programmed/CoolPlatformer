#include "ToastCollectable.h"

#include "CollectableTracker.h"

namespace GAME_NAME::Objects::Collectables
{
	ToastCollectable::ToastCollectable(Vec2 position, Vec2 scale, Sprite* sprite, size_t saveID)
		: BasicCollectable(position, scale, sprite, saveID)
	{

	}

	void ToastCollectable::onCollect()
	{
		CollectableTracker::AddCollectable(CollectableTracker::COLLECTABLE_TYPE::TOAST);
	}
}

