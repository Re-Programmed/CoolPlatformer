#include "Renderer.h"
#include <iostream>
#include "../../Utils/CollisionDetection.h"

namespace GAME_NAME
{
	namespace Rendering
	{
		constexpr int chunkSize = 0x200;

		constexpr int levelSizeX = 30;
		constexpr int levelSizeY = 5;
		unsigned int spriteCount, bgCount;

		Chunk Renderer::m_chunks[levelSizeX * levelSizeY];

		std::vector<GameObject*> Renderer::m_activeGameObjects[MICRO_RENDER_LAYER_COUNT];

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

		void Renderer::LoadObjects(GameObject* objects[], const unsigned int size)
		{
			for (unsigned int i = 0; i < size; i++)
			{
				LoadObject(objects[i]);
			}
		}
#define AsChunkPosition(x) (x >> 9)

		void Renderer::LoadObject(GameObject* object)
		{
			int chunkX = AsChunkPosition(static_cast<int>(object->GetPosition().X)) * levelSizeY;
			int chunkY = AsChunkPosition(static_cast<int>(object->GetPosition().Y));

			Renderer::m_chunks[chunkX + chunkY].Instantiate(object);
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

		void Renderer::Render(Camera::Camera* camera, Vec2* windowSize, RENDER_LAYER layer, GLFWwindow* window, float parallax)
		{
			constexpr unsigned int cameraBoundsPadding = chunkSize;

			//Define const variables.
			Vec2 cameraPosition = camera->GetPosition()/parallax;
			iVec2 cameraBoundingBox = (camera->GetZoom() != 1 ? (*windowSize) * (1 / camera->GetZoom()) + (cameraBoundsPadding << 1) : (*windowSize) + cameraBoundsPadding) + Vec2(0, chunkSize);

			if (layer == RENDER_LAYER_ACTIVE_OBJECTS)
			{
				Vec2 cameraPositionPadding = cameraPosition - cameraBoundsPadding / 2.f;
				//Render active objects if they are on screen. Renders in order of layers from greatest to least.
				for (int i = MICRO_RENDER_LAYER_COUNT; i > 0; i--)
				{
					for (GameObject* obj : m_activeGameObjects[i])
					{
						if (Utils::CollisionDetection::PointWithinBoxBL(obj->GetPosition(), cameraPositionPadding, cameraBoundingBox))
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

			//Loop over chunks that are before the right edge of the camera.
			for (int i = cameraChunkPosition.GetX() * levelSizeY + cameraChunkPosition.GetY(); i < AsChunkPosition((int)cameraPosition.X + cameraBoundingBox.GetX()) * levelSizeY; i++)
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

		}

#pragma region GUIRenderer

		GLuint Renderer::GUIRenderer::startIndex = NULL;

		GLuint Renderer::GUIRenderer::LoadGUIElement(const char* file)
		{
			GLuint ret = loadImage(file);
			if (startIndex == NULL) { startIndex = ret; }

			return ret - startIndex;

		}


#pragma endregion


	}
}