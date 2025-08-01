#pragma once
#include "./GameObject.h"
#include <vector>
#include "../Rendering/Camera/Camera.h"
#include "../Utils/Math/Vec3.h"
#include "../Rendering/Sprite.h"

#include <mutex>

using namespace GAME_NAME::Rendering;

#define CHUNK_OBJECT_RENDER_LAYER_COUNT 4 //Same as MICRO_LAYER_RENDER_COUNT

namespace GAME_NAME
{

	namespace Objects
	{
		enum RENDER_LAYER
		{
			RENDER_LAYER_BG, //BG IS TEXTURES SHOWN IN THE BACKGROUND AS A GRID (EX. THE SKY)
			RENDER_LAYER_OBJECTS, //OBJECTS ARE GAME OBJECTS THAT WILL NOT MOVE, BUT CAN STILL HAVE COMPONENTS (EX. THE GROUND AND GRASS) ,
			RENDER_LAYER_ACTIVE_OBJECTS, //[THE SPRITE RENDER CALL IS NOT PASSED BY A CHUNK, BUT EACH GAME OBJECT] SPRITES ARE GAME OBJECTS THAT WILL BE MOVING AND CHANGING OFTEN (EX. THE PLAYER AND ENEMIES)
			RENDER_LAYER_OBJECTS_FRONT, //FRONT OBJECTS ARE GAME OBJECTS THAT WILL NOT MOVE, BUT CAN STILL HAVE COMPONENTS (EX. THE GROUND AND GRASS) [RENDERED AFTER ACTIVE OBJECTS]
			RENDER_LAYER_GUI
		};

		using namespace MathUtils;
		//Used to group GameObjects on the object layer together to improve culling and render speed.
		class Chunk
		{
		public:
			Chunk();
			Chunk(Vec2 position, Sprite* bgSprite) : m_position(position), m_bgSprite(bgSprite)
			{
				m_objects[0].reserve(5);
				m_objects[1].reserve(8);
				m_objects[2].reserve(3);
			};

			//Copy constructor. (adding mutex made c++ forgor how to copy a Chunk object...)
			Chunk(const Chunk& other)
				: m_position(other.m_position), m_bgSprite(other.m_bgSprite)
			{

			}

			//Move constructor.
			Chunk(Chunk&& other) noexcept
				: m_position(other.m_position), m_bgSprite(other.m_bgSprite)
			{
				other.m_bgSprite = nullptr;
				other.m_position = NULL;
			}

			void Instantiate(GameObject* object, uint8_t layer = 1, bool front = false);	//Load an object to this chunk.

			std::vector<GameObject*>* GetObjects();						//Get all the objects in this chunk.
			std::vector<GameObject*>& GetFrontObjects();				//Get all the front in this chunk.

			void Render(const Vec2 cameraPosition, const int chunkSize, RENDER_LAYER layer, GLFWwindow* window, int microLayer = -1);

			Vec2 GetPosition();											//Get the position of this chunk.

			Chunk& operator=(const Chunk& other)
			{
				m_bgSprite = other.m_bgSprite;
				m_position = other.m_position;

				return *this;
			}

			Chunk& operator=(Chunk&& other) noexcept
			{
				m_bgSprite = other.m_bgSprite;
				m_position = other.m_position;
				
				other.m_bgSprite = nullptr;
				other.m_position = NULL;

				return *this;
			}

			inline void ClearObjects()
			{
				for (int i = 0; i < CHUNK_OBJECT_RENDER_LAYER_COUNT; i++)
				{
					for (GameObject* go : m_objects[i])
					{
						delete go;
					}

					m_objects[i].clear();
				}

				for (GameObject* go : m_frontObjects)
				{
					delete go;
				}

				m_frontObjects.clear();
			}

		private:
			std::vector<GameObject*> m_objects[CHUNK_OBJECT_RENDER_LAYER_COUNT];							//All objects in this chunk.
			std::mutex m_objectsLock;

			std::vector<GameObject*> m_frontObjects;					//All high priority objects in this chunk. (Like genesis priority bit)

			Vec2 m_position;

			Sprite* m_bgSprite;											//The background sprite. This is drawn to the background layer.
		};

	}
}