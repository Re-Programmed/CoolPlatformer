#pragma once

#include "../../../../Objects/GameObject.h"

#include "../../../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

using namespace GAME_NAME::MathUtils;

using namespace GAME_NAME::Components::Physics::Collision;

namespace GAME_NAME::Objects::Environment
{
	class Trampoline
		: public StaticBoxCollisionObject
	{
	public:

		Trampoline(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float bounceFactor);

		//void Update(GLFWwindow* window) override;
		//void Render(const Vec2& cameraPos) override;

		inline float GetBounceFactor() { return m_bounceFactor; }

	private:
		const float m_bounceFactor;

		static bool onCollision(Vec2 push, GameObject* self, GameObject* other);
	};
}