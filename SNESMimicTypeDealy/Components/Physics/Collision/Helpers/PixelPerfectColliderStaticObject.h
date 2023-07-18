#pragma once
#include "../../../../Utils/Math/Vec2.h"
#include "../../../../Rendering/Sprite.h"
#include "../../Collision/CollisionManager.h"
#include "../PixelPerfectCollider.h"
#include "../../../../Objects/GameObject.h"

namespace GAME_NAME::Components::Physics::Collision::Helpers
{
	using namespace MathUtils;

	class PixelPerfectColliderStaticObject
		: public Objects::GameObject
	{
	public:
		PixelPerfectColliderStaticObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite, PixelPerfectCollider::PIXEL_COLLISION_FACE pixels[PixelColliderSize * PixelColliderSize])
			: m_collider(new PixelPerfectCollider(pixels)), Objects::GameObject(position, scale, sprite)
		{
			m_collider->Init(this);
		}

		~PixelPerfectColliderStaticObject()
		{
			delete m_collider;
		}

		void Update(GLFWwindow* window)
		{
			CollisionManager::RegisterStaticColliderToBuffer(m_collider);
		}

	private:
		PixelPerfectCollider* const m_collider;
	};
}