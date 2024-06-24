#pragma once
#include <cstdint>
#define _USE_MATH_DEFINES
#include <math.h>

namespace GAME_NAME
{
	namespace MathUtils
	{
#define M_3_PI_4 2.35619449019	//STORED FOR EFFICIENCY: 3pi/4
#define M_3_PI_4f 2.35619449019f //STORED FOR EFFICIENCY: 3pi/4

#define M_PIf 3.14159265358979323846f

#define MATHUTILS_INVSQRT2 0.707106781187 //STORED FOR EFFICIENCY: 1/sqrt(2)
#define MATHUTILS_INVSQRT2f 0.707106781187f //STORED FOR EFFICIENCY: 1/sqrt(2)

		///Silly function some guy came up with that maybe is fast but probably dosent matter on modern devices.
		float inv_sqrtf(float number)
		{
			union {
				float f;
				uint32_t i;
			} conv;

			float x2;
			const float threehalfs = 1.5F;

			x2 = number * 0.5F;
			conv.f = number;
			conv.i = 0x5f3759df - (conv.i >> 1);
			conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
			return conv.f;
		}

		inline float to_radf(float number)
		{
			return (number / 180.f) * M_PIf;
		}
	}
}