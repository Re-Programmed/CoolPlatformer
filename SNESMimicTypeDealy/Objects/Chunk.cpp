#include "Chunk.h"
#include "../glad/include/glad/glad.h"
namespace GAME_NAME
{

	namespace Objects
	{
		Chunk::Chunk()
			: m_position(Vec2::Zero), m_bgSprite(nullptr)
		{

		}

		/// <summary>
		/// (Cannot be called during rendering) Adds object to chunk renderer.
		/// </summary>
		void Chunk::Instantiate(GameObject object)
		{
			m_objects.push_back(object);
		}

		void Chunk::Render(Vec2 cameraPosition, const int chunkSize)
		{
			if (m_bgSprite != nullptr)
			{
				m_bgSprite->Render(cameraPosition, m_position << 9, chunkSize);
			}

			for (GameObject obj : m_objects)
			{
				obj.Render(cameraPosition);
			}
		}

		Vec2 Chunk::GetPosition()
		{
			return m_position;
		}

	}
}