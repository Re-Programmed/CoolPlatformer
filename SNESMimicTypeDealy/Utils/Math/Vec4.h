#pragma once
#include "Vec3.h"
namespace GAME_NAME
{

    namespace MathUtils
    {
        class Vec4 :
            public Vec3
        {
        public:
            float W;

            Vec4(float x, float y, float z, float w)
                : Vec3(x, y, z)
            {
                W = w;
            }

            Vec4(float xyzw)
                : Vec3(xyzw, xyzw, xyzw)
            {
                W = xyzw;
            }

            /// <summary>
            /// Returns a new Vec4 that represents the Vec4 (percentage) amount between (first) and (second).
            /// </summary>
            /// <param name="first">[Vec4] - Starting Vec4.</param>
            /// <param name="second">[Vec4] - Ending Vec4.</param>
            /// <param name="percentage">[double] - How close to ending vector.</param>
            /// <param name="lerpW">[bool] - If false, LerpBetween will ignore the W paramater. (useful for colors and maintaining opacity)</param>
            /// <returns></returns>
            static Vec4 LerpBetween(const Vec4& first, const Vec4& second, double percentage, bool lerpW = true);
        };

    }
}