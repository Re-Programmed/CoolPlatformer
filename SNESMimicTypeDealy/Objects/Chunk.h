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
		using namespace MathUtils;
		class Chunk
		{
		public:
			Chunk();
			Chunk(Vec2 position, Sprite* bgSprite) : m_position(position), m_bgSprite(bgSprite) {};

			void Instantiate(GameObject object);

			
			void Render(const Vec2 cameraPosition, const int chunkSize);

			Vec2 GetPosition();

		private:
			std::vector<GameObject> m_objects;

			Vec2 m_position;

			Sprite* m_bgSprite;
		};

	}
}