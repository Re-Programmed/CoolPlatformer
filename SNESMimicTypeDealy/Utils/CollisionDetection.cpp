#include "CollisionDetection.h"
#include "../Debug/DebugLog.h"

bool GAME_NAME::Utils::CollisionDetection::PointWithinBoxCenter(iVec2 point, iVec2 boxCenter, iVec2 boxSize)
{
	return valueWithinScale(point.GetX(), boxCenter.GetX(), boxSize.GetX()) && valueWithinScale(point.GetY(), boxCenter.GetY(), boxSize.GetY());
}

bool GAME_NAME::Utils::CollisionDetection::PointWithinBoxBL(iVec2 point, iVec2 boxCorner, iVec2 boxSize)
{
	return valueWithinScaleFromLowest(point.GetX(), boxCorner.GetX(), boxSize.GetX()) && valueWithinScaleFromLowest(point.GetY(), boxCorner.GetY(), boxSize.GetY());
}

bool GAME_NAME::Utils::CollisionDetection::PointWithinBoxBL(Vec2 point, Vec2 boxCorner, Vec2 boxSize)
{
	return valueWithinScaleFromLowest(point.X, boxCorner.X, boxSize.X) && valueWithinScaleFromLowest(point.Y, boxCorner.Y, boxSize.Y);
}

bool GAME_NAME::Utils::CollisionDetection::BoxWithinBox(Vec2 box1BottomLeft, Vec2 box1Size, Vec2 box2BottomLeft, Vec2 box2Size)
{
	if (PointWithinBoxBL(box1BottomLeft + Vec2(box1Size.X, 0), box2BottomLeft, box2Size))
		return true;
	if (PointWithinBoxBL(box1BottomLeft + box1Size, box2BottomLeft, box2Size))
		return true;
	if (PointWithinBoxBL(box1BottomLeft, box2BottomLeft, box2Size))
		return true;
	if (PointWithinBoxBL(box1BottomLeft + Vec2(box1Size.X, 0), box2BottomLeft, box2Size))
		return true;

	return false;
}

bool GAME_NAME::Utils::CollisionDetection::BoxWithinBox(Vec2 box1BottomLeft, Vec2 box1Size, Vec2 box2BottomLeft, Vec2 box2Size, Vec2& push)
{
	if (PointWithinBoxBL(box1BottomLeft + Vec2(box1Size.X, 0), box2BottomLeft, box2Size))
	{
		Vec2 s = GetSideInteresctLength(box1BottomLeft + Vec2(box1Size.X, 0), box2BottomLeft + Vec2(0, box2Size.Y));

		if (s.Y <= s.X)
		{
			push = Vec2(0, s.Y);
			return true;
		}

		if (s.X < s.Y)
		{
			push = Vec2(-s.X, 0);
			return true;
		}
		return true;
	}

	if (PointWithinBoxBL(box1BottomLeft + box1Size, box2BottomLeft, box2Size))
	{
		Vec2 s = GetSideInteresctLength(box1BottomLeft + box1Size, box2BottomLeft);
		if (s.Y <= s.X)
		{
			push = Vec2(0, -s.Y);
			return true;
		}

		if (s.X < s.Y)
		{
			push = Vec2(-s.X, 0);
			return true;
		}
		return true;
	}

	if (PointWithinBoxBL(box1BottomLeft, box2BottomLeft, box2Size))
	{
		Vec2 s = GetSideInteresctLength(box1BottomLeft, box2BottomLeft + box2Size);
		if (s.Y <= s.X)
		{
			push = Vec2(0, s.Y);
			return true;
		}

		if (s.X < s.Y)
		{
			push = Vec2(s.X, 0);
			return true;
		}
		return true;
	}

	if (PointWithinBoxBL(box1BottomLeft + Vec2(0, box1Size.Y), box2BottomLeft, box2Size))
	{
		Vec2 s = GetSideInteresctLength(box1BottomLeft + Vec2(0, box1Size.Y), box2BottomLeft + Vec2(box2Size.X, 0));
		if (s.Y <= s.X)
		{
			push = Vec2(0, -s.Y);
			return true;
		}

		if (s.X < s.Y)
		{
			push = Vec2(s.X, 0);
			return true;
		}
		return true;
	}

	return false;
}

GAME_NAME::MathUtils::Vec2 GAME_NAME::Utils::CollisionDetection::GetSideInteresctLength(Vec2 intersectionPoint1, Vec2 intersectionPoint2)
{
	return Vec2(std::abs(intersectionPoint2.X - intersectionPoint1.X), std::abs(intersectionPoint2.Y - intersectionPoint1.Y));
}

bool GAME_NAME::Utils::CollisionDetection::valueWithinScale(int value, int center, int scale)
{
	return value < center + (scale >> 1) && value > center - (scale >> 1);
}

bool GAME_NAME::Utils::CollisionDetection::valueWithinScaleFromLowest(int value, int lowest, int scale)
{
	return value < lowest + scale && value > lowest;
}

bool GAME_NAME::Utils::CollisionDetection::valueWithinScaleFromLowest(float value, float lowest, float scale)
{
	return value < lowest + scale && value > lowest;
}