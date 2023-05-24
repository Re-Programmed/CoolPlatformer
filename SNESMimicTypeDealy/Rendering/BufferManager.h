#pragma once
namespace GAME_NAME
{

	namespace Rendering
	{
		class BufferManager
		{
		public:
			static void GenBuffers();
		private:
			static GLuint m_vertexBuffer;
		};
	}
}