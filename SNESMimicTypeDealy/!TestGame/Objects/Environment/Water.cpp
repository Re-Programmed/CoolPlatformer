#include "Water.h"
#include "../../../Rendering/Renderers/Renderer.h"
#include "../../TestGame.h"
#include "../../../Utils/CollisionDetection.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			Water::Water(Vec2 position, Vec2 scale)
				: GameObject(position, scale, Rendering::Renderer::GetSprite(WaterSprite)), m_reflectionPosition(Vec2(position.X, position.Y + scale.Y))
			{
				std::vector<GameObject*> bakedReflections = Renderer::GetAllChunkObjectsInArea(Vec2(position.X, m_reflectionPosition.Y), scale);
					
				int r = 0;
				for (GameObject* obj : bakedReflections)
				{
					//Random fluctuation in rate of reflection distortion.
					m_randomSinEffects.push_back(0.5f + (std::rand() / RAND_MAX));

					const Vec2 pos = obj->GetPosition();
					Vec2 scale = obj->GetScale();

					const float percXM = std::clamp(1.0f - (((pos.X + scale.X) - m_position.X) / scale.X), 0.0f, 1.0f);
					const float percXG = std::clamp((((m_position.X + m_scale.X) - pos.X) / scale.X), 0.0f, 1.0f);

					const float percYM = std::clamp(1.0f - ((m_position.Y + m_scale.Y) - pos.Y) / scale.Y, 0.0f, 1.0f);
					const float percYG = std::clamp(1.0f - (((m_position.Y + 2 * m_scale.Y) - pos.Y) / scale.Y), 0.0f, 1.0f);

					Vec2 vertices[4]{
						Vec2(percXM, percYG),
						Vec2(percXM, percYM),
						Vec2(percXG, percYM),
						Vec2(percXG, percYG)
					};

					const float v1Colors = 2.f - (pos.Y - m_position.Y) / m_scale.Y;
					const float v2Colors = 2.f - ((pos.Y + scale.Y) - m_position.Y) / m_scale.Y;

					Vec4 textureColor[4]
					{
						Vec4(1.f, 1.f, 1.f, v1Colors),
						Vec4(1.f, 1.f, 1.f, v2Colors),
						Vec4(1.f, 1.f, 1.f, v2Colors),
						Vec4(1.f, 1.f, 1.f, v1Colors)
					};
					const float check = std::clamp((m_scale.X / 2) - ((scale.X / 2) + std::abs((pos.X + scale.X / 2) - (m_position.X + m_scale.X / 2))), 0.f, 25.f) / 25.f;

					m_bakedReflections.push_back(std::make_unique<BakedReflection>(GameObject(Vec2(pos.X, (2 * m_reflectionPosition.Y) - pos.Y - scale.Y), scale, obj->GetSprite()), std::make_unique<DynamicSprite>(obj->GetSprite()->GetSpriteId(), vertices, vertices, textureColor), Vec4(percXM, percXG, percYM, percYG), check));
				
					r++;
				}
			}

			void Water::Update(GLFWwindow* window)
			{
				checkPlayerIn();

				const float sin = (float)(std::sin(glfwGetTime()) / 5.0);
				const float sin1 = (float)(std::sin(glfwGetTime() * 1.1) / 5.0);
				const float sin2 = (float)(std::sin(glfwGetTime() * 1.2) / 5.0);
				const float sin3 = (float)(std::sin(glfwGetTime() * 1.3) / 5.0);

				const Vec2 camPos = TestGame::INSTANCE->GetCamera()->GetPosition();
				for (int i = 0; i < m_bakedReflections.size(); i++)
				{
					const float check = m_bakedReflections[i]->Check;

					const float percXM = m_bakedReflections[i]->Perc.X;
					const float percXG = m_bakedReflections[i]->Perc.Y;
					const float percYM = m_bakedReflections[i]->Perc.Z;
					const float percYG = m_bakedReflections[i]->Perc.W;

					Vec2 vertices[4]{
						Vec2(percXM + sin * check * m_randomSinEffects[i], percYG),
						Vec2(percXM + sin1 * check * m_randomSinEffects[i], percYM),
						Vec2(percXG + sin2 * check * m_randomSinEffects[i], percYM),
						Vec2(percXG + sin3 * check * m_randomSinEffects[i], percYG)
					};


					m_bakedReflections[i]->Sprite->UpdateVertices(vertices);
					GameObject object = m_bakedReflections[i]->Object;
					m_bakedReflections[i]->Sprite->Render(camPos, object.GetPosition(), object.GetScale(), object.GetRotation());
				}

				for (GameObject* obj : Renderer::GetAllActiveObjectsInArea(m_reflectionPosition, m_scale))
				{
					if (obj == nullptr || obj->GetSprite() == nullptr)
					{
						continue;
					}

					const Vec2 pos = obj->GetPosition();
					Vec2 scale = obj->GetScale();

					const float check = std::clamp((m_scale.X/2) - ((scale.X/2) + std::abs((pos.X + scale.X / 2) - (m_position.X + m_scale.X / 2))), 0.f, 25.f) / 25.f;

					const float percXM = std::clamp(1.0f - (((pos.X + scale.X) - m_position.X) / scale.X), 0.0f, 1.0f);
					const float percXG = std::clamp((((m_position.X + m_scale.X) - pos.X) / scale.X), 0.0f, 1.0f);

					const float percYM = std::clamp(1.0f - ((m_position.Y + m_scale.Y) - pos.Y) / scale.Y, 0.0f, 1.0f);
					const float percYG = std::clamp(1.0f - (((m_position.Y + 2 * m_scale.Y) - pos.Y) / scale.Y), 0.0f, 1.0f);


					Vec2 vertices[4]{
						0,0,0,0
					};

					Vec2 texture[4]{0,0,0,0};

					if (obj->GetTextureFlipped())
					{
						vertices[0] = Vec2(percXM + sin * check, percYG);
						vertices[1] = Vec2(percXM + sin1 * check, percYM);
						vertices[2] = Vec2(percXG + sin2 * check, percYM);
						vertices[3] = Vec2(percXG + sin3 * check, percYG);

						texture[0] = Vec2(percXM, percYG);
						texture[1] = Vec2(percXM, percYM);
						texture[2] = Vec2(percXG, percYM);
						texture[3] = Vec2(percXG, percYG);	
					}
					else {
						vertices[2] = Vec2(percXM + sin * check, percYG);
						vertices[3] = Vec2(percXM + sin1 * check, percYM);
						vertices[0] = Vec2(percXG + sin2 * check, percYM);
						vertices[1] = Vec2(percXG + sin3 * check, percYG);

						texture[0] = Vec2(percXG, percYM);
						texture[1] = Vec2(percXG, percYG);
						texture[2] = Vec2(percXM, percYG);
						texture[3] = Vec2(percXM, percYM);
					}


					const float v1Colors = 2.f - (pos.Y - m_position.Y) / m_scale.Y;
					const float v2Colors = 2.f - ((pos.Y + scale.Y) - m_position.Y) / m_scale.Y;

					Vec4 textureColor[4]
					{
						Vec4(1.f, 1.f, 1.f, v1Colors),
						Vec4(1.f, 1.f, 1.f, v2Colors),
						Vec4(1.f, 1.f, 1.f, v2Colors),
						Vec4(1.f, 1.f, 1.f, v1Colors)
					};

					DynamicSprite(obj->GetSprite()->GetSpriteId(), vertices, texture, textureColor).Render(camPos, Vec2(pos.X + (obj->GetTextureFlipped() ? 0 : scale.X), (2 * m_reflectionPosition.Y) - pos.Y - scale.Y), scale * Vec2((obj->GetTextureFlipped() ? 1.f : -1.f), 1.f));
				}
			}

			void Water::checkPlayerIn()
			{
				if (!m_playerIn)
				{
					if (CollisionDetection::BoxWithinBox(TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale(), m_position, m_scale))
					{
						m_playerIn = true;
						TestGame::ThePlayer->SetSwimming(true);
					}
				}
				else {
					if (!CollisionDetection::BoxWithinBox(TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale(), m_position, m_scale))
					{
						m_playerIn = false;
						TestGame::ThePlayer->SetSwimming(false);
					}
				}
			}

		}
	}
}  