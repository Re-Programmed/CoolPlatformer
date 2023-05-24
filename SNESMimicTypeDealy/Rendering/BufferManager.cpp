#include "../glad/include/glad/glad.h"
#include "BufferManager.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GAME_NAME
{

	namespace Rendering
	{
		typedef struct {

			GLfloat position[2];
			GLfloat textureCoords[2];

		} vertexData;

		vertexData vertices[] = {
			{{ 0.0f, 0.0f }, { 1.0f, 1.0f }},
			{{ 1.0f, 0.0f }, { 0.0f, 1.0f }},
			{{ 1.0f, 1.0f }, { 0.0f, 0.0f }},
			{{ 0.0f, 1.0f }, { 1.0f, 0.0f }}
		};

		GLuint BufferManager::m_vertexBuffer;

		void BufferManager::GenBuffers()
		{
			glGenBuffers(1, &m_vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(2, GL_FLOAT, sizeof(vertexData), (GLvoid*)offsetof(vertexData, position));

			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, sizeof(vertexData), (GLvoid*)offsetof(vertexData, textureCoords));
		}
	}
}