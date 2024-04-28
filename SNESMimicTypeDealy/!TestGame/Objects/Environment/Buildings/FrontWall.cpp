#include "FrontWall.h"

#include "../../../../Rendering/DynamicSprite.h"
#include "../../../TestGame.h"
#include "../../../../Utils/CollisionDetection.h"

#define FRONT_WALL_FADE_INCREMENT 0.0525f

#define FRONT_WALL_BASE_PLAYER_DISTANCE 14.5f

namespace GAME_NAME::Objects::Environment::Buildings
{
	FrontWall::FrontWall(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, std::shared_ptr<BuildingZone> buildingZone, float baseOpacity)
		: GameObject(position, scale, sprite),
		m_baseOpacity(baseOpacity), m_isClear(false),
		m_buildingZone(buildingZone)
	{

	}

	void FrontWall::Render(const Vec2 cameraPosition)
	{
		if (m_opacity >= 1.f) { GameObject::Render(cameraPosition); }

		if (m_isClear)
		{
			if (m_opacity > 0.f)
			{
				m_opacity -= FRONT_WALL_FADE_INCREMENT;
			}
			else {
				return;
			}
		}
		else {
			if (m_opacity < m_baseOpacity)
			{
				m_opacity += FRONT_WALL_FADE_INCREMENT;
			}
		}

		Rendering::DynamicSprite ds(m_sprite->GetSpriteId());

		Vec4 color[4] {
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity),
				Vec4(1.f, 1.f, 1.f, m_opacity)
		};

		Vec2 verts[4] = {
			Rendering::DynamicSprite::DefaultVerts[0],
			{ 0.f, m_opacity/m_baseOpacity },
			{ 1.f, m_opacity/m_baseOpacity },
			Rendering::DynamicSprite::DefaultVerts[3]
		};

		ds.UpdateVertices(verts);
		ds.UpdateTextureVerticies(verts);
		ds.UpdateTextureColor(color);

		ds.Render(cameraPosition, m_position, m_scale, m_rotation);
		
	}

	void FrontWall::Update(GLFWwindow* window)
	{
		//Check if the player is near the front wall, then hide it accordingly.
		BuildingZone& zone = *m_buildingZone;
		m_isClear = CollisionDetection::BoxWithinBox(TestGame::ThePlayer->GetPosition(), TestGame::ThePlayer->GetScale(), Vec2(zone.Position.X - FRONT_WALL_BASE_PLAYER_DISTANCE / 2, zone.Position.Y - FRONT_WALL_BASE_PLAYER_DISTANCE / 2), Vec2(zone.Scale.X + FRONT_WALL_BASE_PLAYER_DISTANCE, zone.Scale.Y + FRONT_WALL_BASE_PLAYER_DISTANCE));
	}

	FrontWall::~FrontWall()
	{
		GameObject::~GameObject();
	}
}