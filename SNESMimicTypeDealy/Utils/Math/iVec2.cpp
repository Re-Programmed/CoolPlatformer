#include "iVec2.h"
namespace GAME_NAME {

	namespace MathUtils
	{
		iVec2 iVec2::Zero(0, 0);

	

		
		iVec2::iVec2(Vec2 v)
			: m_X(v.X), m_Y(v.Y)
		{

		}

		Vec2 iVec2::ToVec2()
		{
			return Vec2(m_X, m_Y);
		}

	}
}