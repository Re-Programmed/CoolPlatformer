#pragma once
namespace GAME_NAME
{

	namespace Rendering
	{
		//Manages buffers for rendering.
		class BufferManager
		{
		public:
			//Must be called before rendering anything.
			static void GenBuffers();
		private:
			static GLuint m_vertexBuffer;
		};
	}
}