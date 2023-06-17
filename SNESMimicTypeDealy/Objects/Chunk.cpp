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
		void Chunk::Instantiate(GameObject* object, bool front)
		{
			if (front)
			{
				m_frontObjects.push_back(object);
			} else {
				m_objects.push_back(object);
			}
		}

		Vec2 Chunk::GetPosition()
		{
			return m_position;
		}

		std::vector<GameObject*> Chunk::GetObjects()
		{
			return m_objects;
		}

		void Chunk::Render(const Vec2 cameraPosition, const int chunkSize, RENDER_LAYER layer, GLFWwindow* window)
		{
			switch (layer)
			{
			case RENDER_LAYER_BG:
				if (m_bgSprite != nullptr)
				{
					m_bgSprite->Render(cameraPosition, m_position << ChunkShift, chunkSize);
				}
				break;
			case RENDER_LAYER_OBJECTS:
				for (GameObject* obj : m_objects)
				{
					obj->Update(window);
					obj->Render(cameraPosition);
				}
				break;
			case RENDER_LAYER_OBJECTS_FRONT:
				for (GameObject* obj : m_frontObjects)
				{
					obj->Update(window);
					obj->Render(cameraPosition);
				}
				break;
			default:
				break;
			}
		}

	}
}