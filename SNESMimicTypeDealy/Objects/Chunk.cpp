#include "Chunk.h"
#include "../glad/include/glad/glad.h"
#include "../Rendering/Renderers/Renderer.h"
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
		void Chunk::Instantiate(GameObject* object, uint8_t layer, bool front)
		{
			if (front)
			{
				m_frontObjects.push_back(object);
			} else {
				m_objects[layer].push_back(object);
			}
		}

		Vec2 Chunk::GetPosition()
		{
			return m_position;
		}

		std::vector<GameObject*>* Chunk::GetObjects()
		{
			return m_objects;
		}

		std::vector<GameObject*>* Chunk::GetFrontObjects()
		{
			return &m_frontObjects;
		}

		void Chunk::Render(const Vec2 cameraPosition, const int chunkSize, RENDER_LAYER layer, GLFWwindow* window)
		{
			switch (layer)
			{
			case RENDER_LAYER_BG:
				if (m_bgSprite != nullptr)
				{
					m_bgSprite->Render(cameraPosition, m_position << ChunkShift, Vec2(-chunkSize, chunkSize));
				}
				break;
			case RENDER_LAYER_OBJECTS:
				for (int i = 0; i < CHUNK_OBJECT_RENDER_LAYER_COUNT; i++)
				{
  					for (GameObject* obj : m_objects[i])
					{
						if(Renderer::UpdateObjects){ obj->Update(window); }
						obj->Render(cameraPosition);
					}
				}
				break;
			case RENDER_LAYER_OBJECTS_FRONT:
				for (GameObject* obj : m_frontObjects)
				{
					if (Renderer::UpdateObjects) { obj->Update(window); }
					obj->Render(cameraPosition);
				}
				break;
			default:
				break;
			}
		}

	}
}