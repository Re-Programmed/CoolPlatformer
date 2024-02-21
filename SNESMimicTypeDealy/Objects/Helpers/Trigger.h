#pragma once

#include "../../!TestGame/TestGame.h"
#include "../../Utils/CollisionDetection.h"

#include "../../Utils/Math/Vec2.h"
#include <functional>

namespace GAME_NAME::Objects
{
	using namespace MathUtils;

	class Trigger
	{
	public:
		Trigger(Vec2 position, Vec2 scale, std::function<void(uint16_t)> callback) : tp_pos(position), tp_scale(scale), tp_callback(callback) {};
	protected:
		void TriggerUpdate()
		{
			if (CollisionDetection::BoxWithinBox(TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale(), tp_pos, tp_scale))
			{
				m_callCount++;
				tp_callback(m_callCount);
				return;
			}

			m_callCount = 0;
		}
	private:
		const std::function<void(uint16_t)> tp_callback;

		const Vec2 tp_pos;
		const Vec2 tp_scale;

		uint16_t m_callCount;
	};
}