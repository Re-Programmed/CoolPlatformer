#pragma once
#include "Vec2.h"
namespace GAME_NAME
{
	namespace MathUtils
	{
		/// <summary>
		/// A final Vec2 made with ints. (For background objects and faster math)
		/// </summary>
		class iVec2
		{
		public:
			static iVec2 Zero;

			iVec2(const int X, const int Y)
				: m_X(X), m_Y(Y)
			{

			}

			iVec2(Vec2 v);

			const int GetX()
			{
				return m_X;
			}

			const int GetY()
			{
				return m_Y;
			}

			Vec2 ToVec2();

		private:
			const int m_X;
			const int m_Y;
		};
	}
}

