#pragma once
#include "./GameObject.h"
#include <vector>
#include "../Rendering/Camera/Camera.h"
#include "../Utils/Math/Vec3.h"
#include "../Rendering/Sprite.h"
using namespace GAME_NAME::Rendering;
namespace GAME_NAME
{

	namespace Objects
	{
		enum RENDER_LAYER
		{
			RENDER_LAYER_BG, //BG IS TEXTURES SHOWN IN THE BACKGROUND AS A GRID (EX. THE SKY)
			RENDER_LAYER_OBJECTS, //OBJECTS ARE GAME OBJECTS THAT WILL NOT MOVE, BUT CAN STILL HAVE COMPONENTS (EX. THE GROUND AND GRASS)
			RENDER_LAYER_SPRITES //[THE SPRITE RENDER CALL IS NOT PASSED BY A CHUNK, BUT EACH GAME OBJECT] SPRITES ARE GAME OBJECTS THAT WILL BE MOVING AND CHANGING OFTEN (EX. THE PLAYER AND ENEMIES)
		};

		using namespace MathUtils;
		class Chunk
		{
		public:
			Chunk();
			Chunk(Vec2 position, Sprite* bgSprite) : m_position(position), m_bgSprite(bgSprite) {};

			void Instantiate(GameObject object);

			void Render(const Vec2 cameraPosition, const int chunkSize, RENDER_LAYER layer);

			Vec2 GetPosition();

		private:
			std::vector<GameObject> m_objects;

			Vec2 m_position;

			Sprite* m_bgSprite;
		};

	}
}