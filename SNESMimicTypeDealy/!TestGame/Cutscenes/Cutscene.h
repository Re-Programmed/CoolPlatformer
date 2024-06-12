#pragma once
#include "../../Utils/Math/Vec2.h"
#include <iostream>

using namespace GAME_NAME::MathUtils;

namespace GAME_NAME::Cutscenes
{
	class Cutscene
	{
	public:
		Cutscene(Vec2 position, float triggerDistance)
			: m_position(position), m_triggerDistance(triggerDistance)
		{
			
		}

		/// <summary>
		/// Returns true if the given position is in the trigger's detection box.
		/// </summary>
		/// <param name="pos">Other position.</param>
		/// <returns></returns>
		bool IsWithin(const Vec2& pos)
		{
			return Vec2::Distance(m_position, pos) < m_triggerDistance;
		}

		/// <summary>
		/// Called when the player enters the radius of this cutscene. Should return false if the trigger event was cancelled.
		/// </summary>
		/// <returns></returns>
		virtual bool Trigger() = 0;
	protected:
		const Vec2 m_position;
		const float m_triggerDistance;
	};
}