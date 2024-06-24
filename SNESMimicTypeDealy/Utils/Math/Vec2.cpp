#include "Vec2.h"
#include <algorithm>
//#define Vec2Zero() (Vec2::Zero)

namespace GAME_NAME
{

	namespace MathUtils
	{
		Vec2 Vec2::Zero(0, 0);
		Vec2 Vec2::OneX(1, 0);
		Vec2 Vec2::OneY(0, 1);
		Vec2 Vec2::MinusOneX(-1, 0);
		Vec2 Vec2::MinusOneXOneY(-1, 1);
		Vec2 Vec2::MinusOneY(0, -1);
		Vec2 Vec2::One(1, 1);

		Vec2::Vec2(float x, float y)
		{
			this->X = x;
			this->Y = y;
		}

		Vec2::Vec2(float xy)
		{
			this->X = xy;
			this->Y = xy;
		}

		//DEBUGGING
		std::string Vec2::ToString()
		{
			return "Vec2 {" + std::to_string(this->X) + ", " + std::to_string(this->Y) + "}";
		}

		void Vec2::Clamp(float min, float max)
		{
			this->X = std::clamp(this->X, min, max);
			this->Y = std::clamp(this->X, min, max);
		}

		void Vec2::Clamp(float minX, float maxX, float minY, float maxY)
		{
			this->X = std::clamp(this->X, minX, maxX);
			this->Y = std::clamp(this->X, minY, maxY);
		}
		float Vec2::Distance(Vec2 a, Vec2 b)
		{
			float aDist = abs(a.X - b.X);
			float bDist = abs(a.Y - b.Y);

			return sqrtf(aDist * aDist + bDist * bDist);
		}

	}
}