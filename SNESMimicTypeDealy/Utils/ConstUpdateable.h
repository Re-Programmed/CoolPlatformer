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
		//An updateable is a class that can be extended to use the Update() method that is called each frame. [CONST updateables will always update and cannot be destroyed.]
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