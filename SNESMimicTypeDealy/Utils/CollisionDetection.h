#pragma once
#include "Math/iVec2.h"
namespace GAME_NAME
{
	using namespace MathUtils;
	namespace Utils
	{
		//Useful functions for collision.
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
			static bool PointWithinBoxBL(Vec2 point, Vec2 boxCorner, Vec2 boxSize);

			static bool BoxWithinBox(Vec2 box1BottomLeft, Vec2 box1Size, Vec2 box2BottomLeft, Vec2 box2Size);
			static bool BoxWithinBox(Vec2 box1BottomLeft, Vec2 box1Size, Vec2 box2BottomLeft, Vec2 box2Size, Vec2& push);

			static Vec2 GetSideInteresctLength(Vec2 intersectionPoint1, Vec2 intersectionPoint2);

		private:
			static bool valueWithinScale(int value, int center, int scale);
			static bool valueWithinScaleFromLowest(int value, int lowest, int scale);

			static bool valueWithinScaleFromLowest(float value, float lowest, float scale);
		};
	}
}