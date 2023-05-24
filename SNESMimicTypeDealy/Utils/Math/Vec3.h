#pragma once
#include "Vec2.h"
namespace GAME_NAME
{

    namespace MathUtils
    {
        class Vec3 :
            public Vec2
        {
        public:
            float Z;

            Vec3(float x, float y, float z)
                : Vec2(x, y)
            {
                Z = z;
            }
        };

    }
}