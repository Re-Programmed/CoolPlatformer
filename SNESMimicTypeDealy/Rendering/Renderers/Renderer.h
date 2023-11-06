#pragma once
#include "../../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../../stbi_image/stbi_image.h"
#include "../../Objects/Chunk.h"
#include "../Camera/Camera.h"
#include "../../Utils/Math/iVec2.h"
#include "../../Objects/GUI/IGUIElement.h"
#include "../DynamicSprite.h"

#define GLOBAL_SPRITE_BASE -6	//Represents the negative number of sprites in the global_sprites directory.
#define SpriteBase(x) (GLOBAL_SPRITE_BASE+x)  //Returns the offset of a sprite from the sprite base.

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
			static DynamicSprite* const GetDynamicSprite(const unsigned int spriteTexture);

			static inline unsigned int GetSpriteCount()
			{
				return spriteCount;
			}

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
			
			/// <summary>
			/// Used for specifying params when instantiating an object. (GameObject*, bool Active, int Layer, bool Front)
			/// </summary>
			typedef struct InstantiateGameObject {
				GameObject* MyObject; //The object to spawn.
				const bool Active; //If it's an active object.
				const int Layer; //The layer to load it on.
				const bool Front; //If it's a front chunk object.

				InstantiateGameObject(GameObject* myObject, bool active, int layer, bool front) : MyObject(myObject), Active(active), Layer(layer), Front(front) { }
			};

			static inline void InstantiateObject(InstantiateGameObject object)
			{
				m_instantiations.push_back(object);
			}

			static inline void DestroyObject(GameObject* object)
			{
				m_destroyQueue.push_back(object);
			}

			static void LoadActiveObjects(GameObject* objects[], const unsigned int size, int layer = 1);
			static void LoadActiveObject(GameObject* object, int layer = 1);

			static inline void LoadGUIElement(GUI::IGUIElement* element, int layer = 1)
			{
				m_guiGameObjects[layer].push_back(element);
			}

			/// <summary>
			/// Must be called before the creation of any objects.
			/// </summary>
			static void InitChunks(std::vector<int> chunkData);

			/// <summary>
			/// Sets a constant to add to all sprite texture indices. (For loading multiple levels at once. The last loaded level will always use positive indices with other levels having negative values.)
			/// </summary>
			/// <param name="fileOffset"></param>
			inline static void SetLastFileOffset(int fileOffset)
			{
				lastFileOff = fileOffset;
			}

			/// <summary>
			/// Returns the constant added to all sprite texture indices.
			/// </summary>
			/// <returns></returns>
			inline static int GetLastFileOffest()
			{
				return lastFileOff;
			}
		private:
			//A constant added to all sprite indices.
			static int lastFileOff;

			//The number of sprites loaded.
			static unsigned int spriteCount;

			/// <summary>
			/// Loads a texture to a buffer.
			/// </summary>
			/// <returns>The buffer loaded to.</returns>
			static GLuint loadImage(const char* file);

			/// <summary>
			/// Objects that need updated no matter where they are in game.
			/// </summary>
			static std::vector<GameObject*> m_activeGameObjects[MICRO_RENDER_LAYER_COUNT];

			static std::vector<GUI::IGUIElement*> m_guiGameObjects[MICRO_GUI_LAYER_COUNT];

			static Chunk m_chunks[];
			static Sprite* const getBackground(const unsigned int bgTexture);

			static std::vector<GameObject*> m_destroyQueue;

			static std::vector<InstantiateGameObject> m_instantiations;

			/// <summary>
			/// Destroys objects in the destroy queue and instantiates all the objects in m_instantiations.
			/// </summary>
			static void updateObjectQueues();

		};


	}
}