#pragma once

#include "../../../Objects/GameObject.h"
#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../../../Rendering/Sprite.h"

using namespace GAME_NAME::Objects;
using namespace GAME_NAME::Rendering;
using namespace GAME_NAME::Components::Physics::Collision;

namespace GAME_NAME::Cutscenes
{
	class AnimatingCharacter
		: public ActiveBoxCollisionGravityObject
	{
	public:
		AnimatingCharacter(Vec2 position, Vec2 scale, Sprite* baseSprite);

	private:
		Vec2 m_targetLocation;

		inline void approachLocation(Vec2 location)
		{
			m_targetLocation = location;
		}
	};
}