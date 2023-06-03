#pragma once
#include <string>
 
namespace GAME_NAME
{

	namespace MathUtils
	{
		class Vec2
		{
		public:
			float X, Y;

			Vec2(float x, float y);
			Vec2(float xy);

			std::string ToString();

			static Vec2 Zero;
			static Vec2 MinusOneX;
			static Vec2 OneX;
			static Vec2 MinusOneY;
			static Vec2 OneY;
			static Vec2 One;

			/// <summary>
			/// Clamps the X and Y to a maximum and minimum value.
			/// </summary>
			/// <param name="min"></param>
			/// <param name="max"></param>
			void Clamp(const float min, const float max);
			/// <summary>
			/// Clamps the X and Y to individual minimums and maximums.
			/// </summary>
			void Clamp(const float minX, const float maxX, const float minY, const float maxY);


			Vec2 operator+ (const Vec2& a)
			{
				return Vec2(this->X + a.X, this->Y + a.Y);
			}

			Vec2 operator* (const Vec2& a)
			{
				return Vec2(this->X * a.X, this->Y * a.Y);
			}

			Vec2 operator* (const float& a)
			{
				return Vec2(this->X * a, this->Y * a);
			}

			Vec2 operator<< (const int shift)
			{
				return Vec2((int)X << shift, (int)Y << shift);
			}

			Vec2 operator>> (const int shift)
			{
				return Vec2((int)X >> shift, (int)Y >> shift);
			}

			Vec2 operator- (const float& a)
			{
				return Vec2(X - a, Y - a);
			}

			Vec2 operator/ (const float& a)
			{
				return Vec2(X / a, Y / a);
			}

			/// <summary>
			/// Uses sqrt, use limitedly.
			/// </summary>
			/// <param name="a"></param>
			/// <param name="b"></param>
			/// <returns></returns>
			static float Distance(Vec2 a, Vec2 b);

		private:

		};
	}
}