#pragma once

#include "PassiveRabbit.h"

namespace GAME_NAME::Objects::Enemies
{
	class FeralRabbit
		: public PassiveRabbit
	{
	public:
		FeralRabbit(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, int jumpingSprite, PassiveRabbitAttributes* attributes = new PassiveRabbitAttributes(), bool beginSleeping = false);

		void Update(GLFWwindow* window) override;

	private:
		/// <summary>
		/// True if the rabbit is sleeping. The rabbit will wake up when the player gets near.
		/// </summary>
		bool m_isAsleep;
	};
}