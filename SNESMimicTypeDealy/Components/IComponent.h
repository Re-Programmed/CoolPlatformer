#pragma once
#include "../Objects/GameObject.h"

#ifndef _ICOMP_DEF
#define _ICOMP_DEF

namespace GAME_NAME
{
	namespace Components
	{
		/// <summary>
		/// A component to apply to an object.
		/// </summary>
		__interface IComponent
		{
			void Update(GLFWwindow* window, Objects::GameObject* object);
			void Init(Objects::GameObject* object);
		};
	}
}

#endif