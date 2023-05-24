#include "CollisionDetection.h"

bool GAME_NAME::Utils::CollisionDetection::PointWithinBoxCenter(iVec2 point, iVec2 boxCenter, iVec2 boxSize)
{
	return valueWithinScale(point.GetX(), boxCenter.GetX(), boxSize.GetX()) && valueWithinScale(point.GetY(), boxCenter.GetY(), boxSize.GetY());
}

bool GAME_NAME::Utils::CollisionDetection::PointWithinBoxBL(iVec2 point, iVec2 boxCorner, iVec2 boxSize)
{
	return valueWithinScaleFromLowest(point.GetX(), boxCorner.GetX(), boxSize.GetX()) && valueWithinScaleFromLowest(point.GetY(), boxCorner.GetY(), boxSize.GetY());
}

bool GAME_NAME::Utils::CollisionDetection::valueWithinScale(int value, int center, int scale)
{
	return value < center + (scale >> 1) && value > center - (scale >> 1);
}

bool GAME_NAME::Utils::CollisionDetection::valueWithinScaleFromLowest(int value, int lowest, int scale)
{
	return value < lowest + scale && value > lowest;
}

