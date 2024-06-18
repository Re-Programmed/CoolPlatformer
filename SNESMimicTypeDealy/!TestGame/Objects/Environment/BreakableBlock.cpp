#include "BreakableBlock.h"

#include "../../../Input/InputManager.h"
#include "../../TestGame.h"
#include "../../../Utils/CollisionDetection.h"

#include "../../../Utils/Time/GameTime.h"

#define BREAKABLE_BLOCK_FADE_SPEED_MULTIPLIER 5.f

namespace GAME_NAME::Objects
{
	double BreakableBlock::m_hoverDisplayPercent = 0.0;

	BreakableBlock::BreakableBlock(Vec2 position, Vec2 scale, Rendering::Sprite* sprite)
		: GameObject(position, scale, sprite)
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
	}
}
