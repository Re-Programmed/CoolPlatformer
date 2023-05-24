#pragma once
#include "Math/iVec2.h"
namespace GAME_NAME
{
	using namespace MathUtils;
	namespace Utils
	{
		class CollisionDetection
		{
		public:
			/// <summary>
			/// Returns if a point is within a box by its center point.
			/// </summary>
			static bool PointWithinBoxCenter(iVec2 point, iVec2 boxCenter, iVec2 boxSize);
			/// <summary>
			/// Returns if a point is within a box by its bottom left.
			/// </summary>
			static bool PointWithinBoxBL(iVec2 point, iVec2 boxCorner, iVec2 boxSize);

		private:
			static bool valueWithinScale(int value, int center, int scale);
			static bool valueWithinScaleFromLowest(int value, int lowest, int scale);
		};
	}
}