#pragma once
#include "../../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../../stbi_image/stbi_image.h"
#include "../../Objects/Chunk.h"
#include "../Camera/Camera.h"
#include "../../Utils/Math/iVec2.h"
#include "../../Objects/GUI/IGUIElement.h"

namespace GAME_NAME
{
	namespace Rendering
	{
#define MICRO_RENDER_LAYER_COUNT 3


		using namespace Objects;
		class Renderer
		{
		public:
			static GLuint LoadSprite(const char* file);
			static GLuint LoadBG(const char* file);

			/// <summary>
			/// Removes all loaded buffers
			/// </summary>
			static void ClearTextures();

			static Sprite* const GetSprite(const unsigned int spriteTexture);

			static void Render(Camera::Camera* camera, Vec2* windowSize, RENDER_LAYER layer, GLFWwindow* window, float parallax = 1.f);

			/// <summary>
			/// Begins drawing the objects in objects. CANNOT BE CALLED DURING RENDERING
			/// </summary>
			/// <param name="objects"></param>
			/// <param name="size"></param>
			static void LoadObjects(GameObject* objects[], const unsigned int size);
			/// <summary>
			/// Begins drawing the object. CANNOT BE CALLED DURING RENDERING
			/// </summary>
			/// <param name="objects"></param>
			/// <param name="size"></param>
			static void LoadObject(GameObject* object);

			static void LoadActiveObjects(GameObject* objects[], const unsigned int size, int layer = 1);
			static void LoadActiveObject(GameObject* object, int layer = 1);

			/// <summary>
			/// Must be called before the creation of any objects.
			/// </summary>
			static void InitChunks(std::vector<int> chunkData);
		private:
			/// <summary>
			/// Loads a texture to a buffer.
			/// </summary>
			/// <returns>The buffer loaded to.</returns>
			static GLuint loadImage(const char* file);

			/// <summary>
			/// Objects that need updated no matter where they are in game.
			/// </summary>
			static std::vector<GameObject*> m_activeGameObjects[MICRO_RENDER_LAYER_COUNT];

			static Chunk m_chunks[];
			static Sprite* const getBackground(const unsigned int bgTexture);



			/// <summary>
			/// For rendering GUI elements.
			/// </summary>
			static class GUIRenderer
			{
			public:
				/// <summary>
				/// Load a file to the GUI texture buffer. Must be called after loading sprites and BG.
				/// </summary>
				/// <param name="file">The file you want to register to the buffer.</param>
				/// <returns>The index of the texture in the buffer relative to the first GUI element registered.</returns>
				static GLuint LoadGUIElement(const char* file);

				static void Init();
			private:
				/// <summary>
				/// The index of the first GUI element in the TextureBuffer.
				/// </summary>
				static GLuint startIndex;

				static void Render(Camera::Camera* camera, Vec2* windowSize);

				static std::vector<GUI::IGUIElement>* elements;

			};
		};


	}
}