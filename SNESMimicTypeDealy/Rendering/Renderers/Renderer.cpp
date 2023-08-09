#include "Renderer.h"
#include <iostream>
#include "../../Utils/CollisionDetection.h"
#include <thread>
#include "../../Settings/SettingsGlobals.h"

namespace GAME_NAME
{
	namespace Rendering
	{
		constexpr int chunkSize = 0x40;

		constexpr int levelSizeX = 30;
		constexpr int levelSizeY = 5;
		unsigned int spriteCount, bgCount;

		Chunk Renderer::m_chunks[levelSizeX * levelSizeY];

		std::vector<GameObject*> Renderer::m_activeGameObjects[MICRO_RENDER_LAYER_COUNT];
		std::vector<GameObject*> Renderer::m_guiGameObjects[MICRO_GUI_LAYER_COUNT];

		std::vector<GameObject*> Renderer::m_instantiations;

		GLuint Renderer::LoadSprite(const char* file)
		{
			spriteCount++;
			return loadImage(file);
		}

		GLuint Renderer::LoadBG(const char* file)
		{
			///DEBUGGING
			if (spriteCount > 0) { std::cout << "LOAD ALL BACKGROUND CONTENT BEFORE LOADING SPRITES." << std::endl; return NULL; }
			bgCount++;
			return loadImage(file);
		}

		Sprite* const Renderer::GetSprite(const unsigned int spriteTexture)
		{
			return new Sprite(spriteTexture + bgCount);
		}

		Sprite* const Renderer::getBackground(const unsigned int bgTexture)
		{
			return new Sprite(bgTexture);
		}

		void Renderer::ClearTextures()
		{
			for (unsigned int i = 0; i < spriteCount + bgCount; i++)
			{
				glDeleteTextures(1, (const GLuint*)i);
			}
		}

		GLuint Renderer::loadImage(const char* file)
		{
			int width, height, channels;
			unsigned char* data = stbi_load(file, &width, &height, &channels, 4);

			if (data == NULL)
			{
				std::cout << stbi_failure_reason() << std::endl;
			}

			GLuint textureBuffer;
			glGenTextures(1, &textureBuffer);
			glBindTexture(GL_TEXTURE_2D, textureBuffer);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST /*GL_LINEAR*/);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST /*GL_LINEAR*/);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			std::cout << "GLBUFFERLOAD: " << textureBuffer << std::endl;

			free(data);

			return textureBuffer;
		}

		void Renderer::InitChunks(std::vector<int> chunkData)
		{
			for (int x = 0; x < levelSizeX; x++)
			{
				for (int y = 0; y < levelSizeY; y++)
				{
					int currChunk = y + static_cast<int>(x * levelSizeY);

					Renderer::m_chunks[currChunk] = Chunk(Vec2(x, y), currChunk >= chunkData.size() ? 0 : (chunkData[currChunk] == 0 ? nullptr : getBackground(chunkData[currChunk])));
				}
			}
		}

		void Renderer::LoadObjects(GameObject* objects[], const unsigned int size, uint8_t layer, bool front)
		{
			for (unsigned int i = 0; i < size; i++)
			{
				LoadObject(objects[i], layer, front);
			}
		}
#define AsChunkPosition(x) (x >> ChunkShift)

		void Renderer::LoadObject(GameObject* object, uint8_t layer, bool front)
		{
			int chunkX = AsChunkPosition(static_cast<int>(object->GetPosition().X)) * levelSizeY;
			int chunkY = AsChunkPosition(static_cast<int>(object->GetPosition().Y));

			Renderer::m_chunks[chunkX + chunkY].Instantiate(object, layer, front);
		}

		void Renderer::LoadActiveObjects(GameObject* objects[], const unsigned int size, int layer)
		{
			for (unsigned int i = 0; i < size; i++)
			{
				LoadActiveObject(objects[i], layer);
			}
		}

		void Renderer::LoadActiveObject(GameObject* object, int layer)
		{
			m_activeGameObjects[layer].push_back(object);
		}

		///Macro for converting to Chunk Coords.
		int renderCalls = 0;
		float tAlloc = 0;
		float m_curr = 0;

		void Renderer::Render(Camera::Camera* camera, Vec2* windowSize, RENDER_LAYER layer, GLFWwindow* window, float parallax)
		{
			Vec2 cameraPosition = camera->GetPosition() / parallax;

			if (layer == RENDER_LAYER_GUI)
			{
				for (uint8_t currLayer = 0; currLayer < MICRO_GUI_LAYER_COUNT; currLayer++)
				{
					for (GameObject* guiObject : m_guiGameObjects[currLayer])
					{
						guiObject->Render(camera->GetPosition());
					}
				}

				return;
			}

			constexpr unsigned int cameraBoundsPadding = chunkSize;

			//Define const variables.

			iVec2 cameraBoundingBox = (camera->GetZoom() != 1 ? (*windowSize) * (1 / camera->GetZoom()) + (cameraBoundsPadding << 1) : (*windowSize) + cameraBoundsPadding) + Vec2(0, chunkSize);

			if (layer == RENDER_LAYER_ACTIVE_OBJECTS)
			{
				Vec2 cameraPositionPadding = cameraPosition - cameraBoundsPadding / 2.f;
				Vec2 cameraBounds = Vec2(cameraBoundingBox.GetX(), cameraBoundingBox.GetY());
				//Render active objects if they are on screen. Renders in order of layers from least to greatest.
				for (int i = 1; i < MICRO_RENDER_LAYER_COUNT; i++)
				{
					for (GameObject* obj : m_activeGameObjects[i])
					{
						if (Utils::CollisionDetection::BoxWithinBox(obj->GetPosition(), obj->GetScale(), cameraPositionPadding, cameraBounds))
						{
							obj->Update(window);
							obj->Render(cameraPosition);
						}
					}
				}

				return;
			}

			iVec2 cameraChunkPosition = AsChunkPosition(cameraPosition);
			const Vec2 cameraPositionS = cameraPosition - cameraBoundsPadding;

			int cameraTopEdge = cameraChunkPosition.GetY() + AsChunkPosition(cameraBoundingBox.GetY());
			//if (AsChunkPosition(cameraBoundingBox.GetY()) >= LEVEL_SIZE_Y * 2) { return; }


			//delete cameraPositionPadding;

			const int iterInit = cameraChunkPosition.GetX() * levelSizeY + cameraChunkPosition.GetY();
			const int iterEnd = AsChunkPosition((int)cameraPosition.X + cameraBoundingBox.GetX()) * levelSizeY;


			//Loop over chunks that are before the right edge of the camera.
			for (int i = iterInit; i < iterEnd; i++)
			{
				//Check if a chunk is within the bounding box of the camera. (MAY NEED BUGFIXED FOR WHEN CAMERA CHANGES ZOOM!!!!!)
				if (m_chunks[i].GetPosition().Y < cameraTopEdge)
				{
					//Render a chunk if it is in the cameras bounding box.
					m_chunks[i].Render(cameraPosition, chunkSize, layer, window);

					
					//Check if the chunk we just rendered is at the top of the screen.
					if ((i % levelSizeY) == (levelSizeY - 1))
					{
						//If the chunk just rendered is at the top of the screen, skip all chunks in the next column below the camera's position.
						i += cameraChunkPosition.GetY();
					}

				}
				else
				{
					//If we tried to render a chunk and failed, skip this entire column.
					i += cameraChunkPosition.GetY() + (levelSizeY - 1) - i % levelSizeY;
				}
			}

			if (layer == RENDER_LAYER_BG)
			{
				for (GameObject* bg2Object : m_activeGameObjects[0])
				{
					bg2Object->Update(window);
					bg2Object->Render(cameraPosition);
				}
			}

		}

		std::vector<GameObject*> Renderer::GetAllObjectsInArea(Vec2 bottomLeft, Vec2 scale, int8_t layer)
		{
			std::vector<GameObject*> ret;
			
			std::thread activeObjectCheck([layer, bottomLeft, scale](std::vector<GameObject*>& ret) {
				if (layer != -1)
				{
					for (GameObject* obj : m_activeGameObjects[layer])
					{
						if (Utils::CollisionDetection::PointWithinBoxBL(obj->GetPosition(), bottomLeft, scale))
						{
							ret.push_back(obj);
						}
					}
				}
				else {
					for (int i = MICRO_RENDER_LAYER_COUNT; i > 0; i--)
					{
						for (GameObject* obj : m_activeGameObjects[i])
						{
							if (Utils::CollisionDetection::PointWithinBoxBL(obj->GetPosition(), bottomLeft, scale))
							{
								ret.push_back(obj);
							}
						}
					}
				}
			}, std::ref(ret));

			iVec2 chunkPos = AsChunkPosition(bottomLeft);
			iVec2 chunkScale = AsChunkPosition(scale);

			const int8_t start = chunkPos.GetX() * levelSizeY + chunkPos.GetY();
			const int8_t endX = chunkScale.GetX();
			const int8_t endY = chunkScale.GetY();

			for (int8_t x = 0; x < endX; x++)
			{
				for (int8_t y = 0; y < endY; y++)
				{
					for (int i = 0; i < CHUNK_OBJECT_RENDER_LAYER_COUNT; i++)
					{
						for (GameObject* add : m_chunks[start + (x * levelSizeY) + y].GetObjects()[i])
						{
							ret.push_back(add);
						}
					}
				}
			}

			if (activeObjectCheck.joinable()) { activeObjectCheck.join(); }

			return ret;
		}

		std::vector<GameObject*> Renderer::GetAllChunkObjectsInArea(Vec2 bottomLeft, Vec2 scale)
		{

			std::vector<GameObject*> ret;
			iVec2 chunkPos = AsChunkPosition(bottomLeft);
			iVec2 chunkScale = AsChunkPosition(scale) + 1;

			const int8_t start = chunkPos.GetX() * levelSizeY + chunkPos.GetY();
			const int8_t endX = chunkScale.GetX();
			const int8_t endY = chunkScale.GetY();

			for (int8_t x = 0; x < endX; x++)
			{
				for (int8_t y = 0; y < endY; y++)
				{
					for (int i = 0; i < CHUNK_OBJECT_RENDER_LAYER_COUNT; i++)
					{
						for (GameObject* add : m_chunks[start + (x * levelSizeY) + y].GetObjects()[i])
						{
							if (Utils::CollisionDetection::BoxWithinBox(add->GetPosition(), add->GetScale(), bottomLeft, scale))
							{
								ret.push_back(add);
							}
						}
					}
				}
			}

			return ret;
		}

		std::vector<GameObject*> Renderer::GetAllActiveObjectsInArea(Vec2 bottomLeft, Vec2 scale, int8_t layer)
		{
			std::vector<GameObject*> ret;
			if (layer != -1)
			{
				for (GameObject* obj : m_activeGameObjects[layer])
				{
					if (Utils::CollisionDetection::BoxWithinBox(obj->GetPosition(), obj->GetScale(), bottomLeft, scale))
					{
						
						ret.push_back(obj);
					}
				}

				return ret;
			}
			else {
				for (int i = 0; i < MICRO_RENDER_LAYER_COUNT; i++)
				{
					for (GameObject* obj : m_activeGameObjects[i])
					{
						if (Utils::CollisionDetection::BoxWithinBox(obj->GetPosition(), obj->GetScale(), bottomLeft, scale))
						{
							ret.push_back(obj);
						}
					}
				}

				return ret;
			}
		}


	}
}