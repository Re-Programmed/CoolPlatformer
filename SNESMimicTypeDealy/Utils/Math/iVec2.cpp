#include "iVec2.h"
namespace GAME_NAME {

	namespace MathUtils
	{
		iVec2 iVec2::Zero(0, 0);

	

		
		iVec2::iVec2(Vec2 v)
			: m_X((const int)v.X), m_Y((const int)v.Y)
		{

		}

		Vec2 iVec2::ToVec2()
		{
			return Vec2((const float)m_X, (const float)m_Y);
		}

	}
}