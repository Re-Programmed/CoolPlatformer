#include "AnimatingCharacter.h"

namespace GAME_NAME::Cutscenes
{

	AnimatingCharacter::AnimatingCharacter(Vec2 position, Vec2 scale, Sprite* baseSprite)
		: ActiveBoxCollisionGravityObject(position, scale, baseSprite), m_targetLocation(position)
	{

	}

}
