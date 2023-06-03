#pragma once
#include "IUpdateable.h"
#include "UpdateManager.h"
#if _DEBUG
#include <iostream>
#endif

namespace GAME_NAME
{
	namespace Utils
	{
		class ConstUpdateable : public IUpdateable
		{
		public:
			ConstUpdateable()
			{
				UpdateManager::RegisterUpdateable(this);
			}
#if _DEBUG

			~ConstUpdateable()
			{
				std::cout << "Destroyed ConstUpdateable, maybe you meant to use RemoveableUpdateable." << std::endl;
			}
#endif
		};
	}
}