#pragma once
#include "../../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../../stbi_image/stbi_image.h"
#include "../../Objects/Chunk.h"
#include "../Camera/Camera.h"
#include "../../Utils/Math/iVec2.h"

namespace GAME_NAME
{
	namespace Rendering
	{
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

			static void Render(Camera::Camera* camera, Vec2* windowSize);


			/// <summary>
			/// Begins drawing the objects in objects. CANNOT BE CALLED DURING RENDERING
			/// </summary>
			/// <param name="objects"></param>
			/// <param name="size"></param>
			static void LoadObjects(GameObject objects[], const unsigned int size);

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


			static Chunk m_chunks[];
			static Sprite* const getBackground(const unsigned int bgTexture);

			

		};
	}
}