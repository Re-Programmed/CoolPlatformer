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
#define MICRO_RENDER_LAYER_COUNT 4
#define MICRO_GUI_LAYER_COUNT 3
		constexpr int ChunkShift = 6;

		using namespace Objects;
		class ActiveObject {
		public:
			ActiveObject(GameObject* object, bool loaded)
				: Object(object), Loaded(loaded)
			{

			}

			GameObject* Object;
			bool Loaded;
		};

		//The main class to draw things to the screen.
		class Renderer
		{
		public:
			//Load a file to the sprite buffer.
			static GLuint LoadSprite(const char* file);
			//Load a file to the BG buffer.
			static GLuint LoadBG(const char* file);

			/// <summary>
			/// Removes all loaded buffers.
			/// </summary>
			static void ClearTextures();

			//Create a sprite from its texture.
			static Sprite* const GetSprite(const unsigned int spriteTexture);

			/// <summary>
			/// Render is called every frame to draw everything to the screen.
			/// </summary>
			/// <param name="camera">The camera to use as a projection matrix.</param>
			/// <param name="windowSize">The size of the window. (Pointer for no reason, should probably be changed to reference)</param>
			/// <param name="layer">The current layer to render.</param>
			/// <param name="window">The window to render to.</param>
			/// <param name="parallax">The amount to parallax off of the camera.</param>
			static void Render(Camera::Camera* camera, Vec2* windowSize, RENDER_LAYER layer, GLFWwindow* window, float parallax = 1.f);

			/// <summary>
			/// Returns every GameObject in an area.
			/// </summary>
			static std::vector<GameObject*> GetAllObjectsInArea(Vec2 bottomLeft, Vec2 scale, int8_t layer = -1);
			/// <summary>
			/// Returns every chunk GameObject in an area.
			/// </summary>
			static std::vector<GameObject*> GetAllChunkObjectsInArea(Vec2 bottomLeft, Vec2 scale);
			/// <summary>
			/// Returns every active GameObject in an area.
			/// </summary>
			static std::vector<GameObject*> GetAllActiveObjectsInArea(Vec2 bottomLeft, Vec2 scale, int8_t layer = -1);

			/// <summary>
			/// Begins drawing the objects in objects. CANNOT BE CALLED DURING RENDERING
			/// </summary>
			/// <param name="objects"></param>
			/// <param name="size"></param>
			static void LoadObjects(GameObject* objects[], const unsigned int size, uint8_t layer = 1, bool front = false);
			/// <summary>
			/// Begins drawing the object. CANNOT BE CALLED DURING RENDERING
			/// </summary>
			/// <param name="objects"></param>
			/// <param name="size"></param>
			static void LoadObject(GameObject* object, uint8_t layer = 1, bool front = false);

			static inline void InstantiateObject(GameObject* object)
			{
				m_instantiations.push_back(object);
			}

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

			static std::vector<GameObject*> m_guiGameObjects[MICRO_GUI_LAYER_COUNT];

			static Chunk m_chunks[];
			static Sprite* const getBackground(const unsigned int bgTexture);

			static std::vector<GameObject*> m_instantiations;

		};


	}
}