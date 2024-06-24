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
			static Vec2 MinusOneXOneY;
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

			Vec2 operator- (const Vec2& a)
			{
				return Vec2(this->X - a.X, this->Y - a.Y);
			}

			Vec2 operator+ (const Vec2& a)
			{
				return Vec2(this->X + a.X, this->Y + a.Y);
			}

			Vec2 operator/ (const Vec2& a)
			{
				return Vec2(this->X / a.X, this->Y / a.Y);
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
				return Vec2((float)((int)X << shift), (float)((int)Y << shift));
			}

			Vec2 operator>> (const int shift)
			{
				return Vec2((float)((int)X >> shift), (float)((int)Y >> shift));
			}

			Vec2 operator- (const float& a)
			{
				return Vec2(X - a, Y - a);
			}

			Vec2 operator/ (const float& a)
			{
				return Vec2(X / a, Y / a);
			}

			void operator+= (const Vec2& v)
			{
				this->X += v.X;
				this->Y += v.Y;
			}

			void operator-= (const Vec2& v)
			{
				this->X -= v.X;
				this->Y -= v.Y;
			}

			/// <summary>
			/// Calculate distance.
			/// </summary>
			/// <param name="a">Vec2 1</param>
			/// <param name="b">Vec2 2</param>
			/// <returns>The distance between a and b.</returns>
			static float Distance(Vec2 a, Vec2 b);

			//Returns the normalized X coord of this vector.
			inline float NormalizeX()
			{
				return X == 0 ? 0.f : (X < 0 ? -1.f : 1.f);
			}

			//Returns the normalized Y coord of this vector.
			inline float NormalizeY()
			{
				return Y == 0 ? 0.f : (Y < 0 ? -1.f : 1.f);
			}

			inline static Vec2 RandVec2(float xUpperBound, float yUpperBound)
			{
				float randX = (float)std::rand() / (float)RAND_MAX; randX *= xUpperBound;
				float randY = (float)std::rand() / (float)RAND_MAX; randY *= yUpperBound;

				return Vec2(randX, randY);
			}
		private:

		};
	}
}