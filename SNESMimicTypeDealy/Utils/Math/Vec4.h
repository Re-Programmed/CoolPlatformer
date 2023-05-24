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
        };

    }
}