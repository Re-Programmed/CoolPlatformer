#include "Vec4.h"
#include <cmath>



namespace GAME_NAME::MathUtils
{
	Vec4 Vec4::LerpBetween(const Vec4& first, const Vec4& second, double percentage, bool lerpW)
	{
		return { (float)std::lerp(first.X, second.X, percentage),
				 (float)std::lerp(first.Y, second.Y, percentage),
				 (float)std::lerp(first.Z, second.Z, percentage),
				 lerpW ? (float)std::lerp(first.W, second.W, percentage) : first.W };
	}
}