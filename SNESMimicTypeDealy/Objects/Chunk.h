#pragma once
#include "./GameObject.h"
#include <vector>
#include "../Rendering/Camera/Camera.h"
#include "../Utils/Math/Vec3.h"
#include "../Rendering/Sprite.h"
using namespace GAME_NAME::Rendering;

#define CHUNK_OBJECT_RENDER_LAYER_COUNT 3

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
			Chunk(Vec2 position, Sprite* bgSprite) : m_position(position), m_bgSprite(bgSprite) {};

			void Instantiate(GameObject* object, uint8_t layer = 1, bool front = false);	//Load an object to this chunk.

			std::vector<GameObject*>* GetObjects();						//Get all the objects in this chunk.
			std::vector<GameObject*>* GetFrontObjects();				//Get all the front in this chunk.

			void Render(const Vec2 cameraPosition, const int chunkSize, RENDER_LAYER layer, GLFWwindow* window, int microLayer = -1);

			Vec2 GetPosition();											//Get the position of this chunk.
		private:
			std::vector<GameObject*> m_objects[CHUNK_OBJECT_RENDER_LAYER_COUNT];							//All objects in this chunk.

			std::vector<GameObject*> m_frontObjects;					//All high priority objects in this chunk. (Like genesis priority bit)

			Vec2 m_position;

			Sprite* m_bgSprite;											//The background sprite. This is drawn to the background layer.
		};

	}
}