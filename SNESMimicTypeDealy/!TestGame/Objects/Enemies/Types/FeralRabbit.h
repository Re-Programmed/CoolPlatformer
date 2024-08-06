#pragma once

#include "PassiveRabbit.h"

namespace GAME_NAME::Objects::Enemies
{
	class FeralRabbit
		: public PassiveRabbit
	{
	public:
		FeralRabbit(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, int jumpingSprite, PassiveRabbitAttributes* attributes = new PassiveRabbitAttributes());

		void Update(GLFWwindow* window) override;
	};
}