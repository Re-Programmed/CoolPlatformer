#include "BreakableBlock.h"

#include "../../../Input/InputManager.h"
#include "../../TestGame.h"
#include "../../../Utils/CollisionDetection.h"

#include "../../../Utils/Time/GameTime.h"

#define BREAKABLE_BLOCK_FADE_SPEED_MULTIPLIER 5.f

namespace GAME_NAME::Objects
{
	double BreakableBlock::m_hoverDisplayPercent = 0.0;
	double BreakableBlock::m_currentMiningTime = 0.0;

	BreakableBlock::BreakableBlock(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, double mineTime, int mineResistance)
		: GameObject(position, scale, sprite), m_mineTime(mineTime), m_mineResistance(mineResistance)
	{

	}

	void BreakableBlock::Render(const Vec2& cameraPosition)
	{
		//Render outline if hovered.
		if(m_isHovered || m_hoverDisplayPercent > 0.0)
		{
			if (m_isHovered)
			{
				m_hoverDisplayPercent += Utils::Time::GameTime::GetScaledDeltaTime() * BREAKABLE_BLOCK_FADE_SPEED_MULTIPLIER;
				if (m_hoverDisplayPercent > 1.0) { m_hoverDisplayPercent = 1.0; }
			}
			else {
				m_hoverDisplayPercent -= Utils::Time::GameTime::GetScaledDeltaTime() * BREAKABLE_BLOCK_FADE_SPEED_MULTIPLIER;
			}

			DynamicSprite* hoveredSprite = new DynamicSprite(Renderer::GetSprite(72)->GetSpriteId());

			Vec4 hoverColor = Vec4::LerpBetween({ 1.f, 1.f, 0.f, 0.f }, { 1.f, 1.f, 0.f, 1.f }, m_hoverDisplayPercent);
			Vec4 hoverVerts[4] = {
				hoverColor,hoverColor,hoverColor,hoverColor
			};

			hoveredSprite->UpdateTextureColor(hoverVerts);

			hoveredSprite->Render(cameraPosition, m_position - Vec2(1), m_scale + Vec2(2));
		}
		
		GameObject::Render(cameraPosition);
	}

	void BreakableBlock::Update(GLFWwindow* window)
	{
		Vec2 mouseWorldPosition = InputManager::GetMouseWorldPosition(TestGame::INSTANCE->GetCamera());
		m_isHovered = Utils::CollisionDetection::PointWithinBoxBL(mouseWorldPosition, m_position, m_scale);

		if (InputManager::GetMouseButton(0))
		{
			//The player is trying to mine this object.
			if (m_isHovered)
			{
				const ItemData data = ITEMTYPE_GetItemData(TestGame::ThePlayer->GetInventory()->GetHeldItem()->GetType());

				//Can the current held item mine stuff?
				if (data.Actions & TOOL_ACTION::MINE)
				{
					//Does the current held item have enough mining power?
					if (std::stoi(data.Attributes.at(TOOL_ACTION::MINE)) >= m_mineResistance)
					{
						m_currentMiningTime += Utils::Time::GameTime::GetScaledDeltaTime();
					}
				}

				//TODO: Create a meter or graphic of some kind.

				//Break this block.
				if (m_currentMiningTime >= m_mineTime)
				{
					//Create particles.
					Particles::ParticleEmitter* pe = new Particles::ParticleEmitter(m_position);
					Renderer::LoadActiveObject(pe);
					pe->RegisterParticle(Particles::Particle(m_position, m_scale / 10.f, std::rand() * 90.f / RAND_MAX - 45.f, { 0.f, 5.f }, std::rand() * 5.f / RAND_MAX, 0.75f, new Sprite(this->m_sprite->GetSpriteId())));
					pe->SpawnParticles(std::rand() * 10 / RAND_MAX + 10, { 5.f, 5.f }, 4.f, std::rand() * 90.f / RAND_MAX - 45.f);

					//Create thread that sleeps until it can delete the particle emitter.
					std::thread particleEmitterRemoval([pe]() {
						std::this_thread::sleep_for(std::chrono::seconds(8));
						Renderer::DestroyActiveObjectImmediate(pe);
						delete pe;
					});

					//Destroy this object.
					Renderer::DestroyObject(this);
					delete this;

					//Reset mining time.
					m_currentMiningTime = 0;
				}
			}
		}
		else {
			//Reset mining time.
			m_currentMiningTime = 0;
		}
	}
}
