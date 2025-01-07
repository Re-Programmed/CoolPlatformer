#pragma once

#include "BasicCollectable.h"

namespace GAME_NAME::Objects::Collectables
{
	class ToastCollectable
		: public BasicCollectable
	{
	public:

		ToastCollectable(Vec2 position, Vec2 scale, Sprite* sprite, size_t saveID);
	protected:
		void onCollect() override;
	};
}