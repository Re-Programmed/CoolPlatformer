#pragma once
#include "../../../Objects/GameObject.h"
#include <vector>

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			/*typedef struct ParallaxObject
			{
				GameObject Object;
				float Amount;
			};*/

			class BackgroundObjects
			{
			public:
				static void TiledBGObject(GameObject tile[], int count, float parallax, GLFWwindow* window);
			private:
				//static std::vector<ParallaxObject> m_bgObjects;
			};
		}
	}
}