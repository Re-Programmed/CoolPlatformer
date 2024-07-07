#include "Sprite.h"
#include "Window.h"

namespace GAME_NAME
{

	namespace Rendering
	{
		Vec2 Sprite::m_resolutionScale = Vec2::One;
		std::vector<std::function<void(Sprite*, const Vec2&, const Vec2&, const float&, VertexData*)>> Sprite::m_prerenderExecutions;

		/// <summary>
		/// The default texture coordinates for an unmodified sprite.
		/// </summary>
		const Vec2 SPRITE_TEXTURE_COORDIANTES[4] {
			Vec2(0.0f, 0.0f), Vec2(0.0f, 1.0f), Vec2(1.0f, 1.0f), Vec2(1.0f, 0.0f)
		};

		const Vec2 SPRITE_VERTICIES[4]{
			Vec2(1.0f, 1.0f), Vec2(1.0f, 0.0f), Vec2(0.0f, 0.0f), Vec2(0.0f, 1.0f)
		};

		//This and other math related to vectors and positions needs to execute on the GPU, figure it out...
		void Sprite::Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale, float rotation)
		{
			glBindTexture(GL_TEXTURE_2D, Renderer::GetTextureIDFromIndex(m_spriteId));
			glLoadIdentity();
			glTranslatef((position.X - cameraPosition.X) * m_resolutionScale.X, (position.Y - cameraPosition.Y) * m_resolutionScale.Y, 0);

			glScalef(scale.X * m_resolutionScale.X, scale.Y * m_resolutionScale.Y, 1.f);

			glRotatef(rotation, 0, 0, 1);

			//glDrawArrays(GL_QUADS, 0, 4);
			glBegin(GL_QUADS);

		//	std::vector<std::thread*> m_vertexThreadBuffer;
			for (uint8_t i = 0; i < 4; i++)
			{
				if (m_prerenderExecutions.size() > 0)
				{
					//Stores what updates the prerenderExecutions have made. This ensures that each gl property is set EXACTLY ONCE.
					VertexData* vdata = new VertexData(SPRITE_VERTICIES[i], SPRITE_TEXTURE_COORDIANTES[i]);

					//Call all vertex executions in parallel.
					for (int func = 0; func < m_prerenderExecutions.size(); func++)
					{
						m_prerenderExecutions[func](this, position, scale, rotation, vdata);
						//TODO: THREADING?
						//m_prerenderExecutions[func](this, SPRITE_VERTICIES[i]);
						/*std::thread ethread([this, i, vdata](int func) {
							m_prerenderExecutions[func](this, SPRITE_VERTICIES[i], vdata);
						}, func);
						//thread.detach();
						m_vertexThreadBuffer.push_back(&ethread);*/
					}
				//	for (auto& thread : m_vertexThreadBuffer) { if (thread->joinable()) { thread->join(); }; delete thread; }
				//	m_vertexThreadBuffer.clear();
					
					//Update params based on what was modified.
					glTexCoord2f(vdata->TextureCoordinate.X, vdata->TextureCoordinate.Y);
					glColor4f(vdata->Color.X, vdata->Color.Y, vdata->Color.Z, vdata->Color.W);
					glVertex2f(vdata->Position.X, vdata->Position.Y);

					delete vdata;
				}
				else {

					//Use default rendering mode.
					glTexCoord2f(SPRITE_TEXTURE_COORDIANTES[i].X, SPRITE_TEXTURE_COORDIANTES[i].Y);
					glColor4f(1.f, 1.f, 1.f, 1.f);
					glVertex2f(SPRITE_VERTICIES[i].X, SPRITE_VERTICIES[i].Y);
				}
			}

			glColor4f(1.f, 1.f, 1.f, 1.f);
			glColor4f(1.f, 1.f, 1.f, 1.f);
			glColor4f(1.f, 1.f, 1.f, 1.f);
			glColor4f(1.f, 1.f, 1.f, 1.f);

			glEnd();
		}

		void Sprite::SetResolution(Vec2 res)
		{
			m_resolutionScale = Vec2(res.X / TargetResolutionX, res.Y / TargetResolutionY);
		}

		const unsigned int Sprite::GetSpriteId()
		{
			return m_spriteId;
		}

		unsigned int Sprite::AddPrerenderExecution(std::function<void(Sprite*, const Vec2&, const Vec2&, const float&, VertexData*)> prerenderExecution)
		{
			m_prerenderExecutions.push_back(prerenderExecution);
			return m_prerenderExecutions.size() - 1;
		}

		

	}
}