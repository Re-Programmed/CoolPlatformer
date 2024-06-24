#include "BackgroundObjects.h"
#include "../../../Rendering/Renderers/Renderer.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{

			void BackgroundObjects::TiledBGObject(GameObject tile[], int count, float parallax, GLFWwindow* window)
			{
				int width;
				glfwGetWindowSize(window, &width, NULL);

				int n = 1 + width/(int)tile->GetScale().X;
				for (int i = 0; i < n; i++)
				{
					int tileP = count * (std::rand() / RAND_MAX);

					GameObject* newObject = &tile[tileP];

					newObject->SetPosition(i * newObject->GetScale().X);

					Rendering::Renderer::InstantiateObject(Rendering::Renderer::InstantiateGameObject(newObject, false, 1, false));
				}
			}
		}
	}
}

