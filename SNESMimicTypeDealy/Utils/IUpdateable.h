#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifndef _IUPDATEABLE_DEF
#define _IUPDATEABLE_DEF

namespace GAME_NAME
{
	namespace Utils
	{
		typedef int UpdateIndex;
		/// <summary>
		/// INFO: 
		/// STATIC UPDATEABLES MUST BE ADDED TO THE m_updateables ARRAY IN UPDATE MANAGER.
		/// </summary>
		__interface IUpdateable
		{
		public:
			void Update(GLFWwindow* window);
		};
	}
}

#endif // !IUPDATEABLE_DEF