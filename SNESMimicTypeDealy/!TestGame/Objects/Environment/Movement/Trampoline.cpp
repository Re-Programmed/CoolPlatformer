#include "Trampoline.h"

#include "../../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../../../TestGame.h"

#define MAX_TRAMPOLINE_VELOCITY 500.f
#define MIN_TRAMPOLINE_VELOCITY 100.f

namespace GAME_NAME::Objects::Environment
{
	Trampoline::Trampoline(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float bounceFactor)
		: StaticBoxCollisionObject(position, scale, sprite), m_bounceFactor(bounceFactor)
	{
		SetOnCollision(onCollision);
	}

	bool Trampoline::onCollision(Vec2 push, GameObject* self, GameObject* other)
	{
		ActiveBoxCollisionGravityObject* abcgo = dynamic_cast<ActiveBoxCollisionGravityObject*>(other);

		if (abcgo)
		{
			float totalYVel = abcgo->GetPhysics()->GetGravitationalVelocity() + abcgo->GetPhysics()->GetVelocity().Y;

			if (totalYVel > 0) { return true; }

			float newVel = -totalYVel * ((Trampoline*)(self))->GetBounceFactor();
			newVel = std::clamp(newVel, MIN_TRAMPOLINE_VELOCITY, MAX_TRAMPOLINE_VELOCITY);

			
			if (abcgo == TestGame::ThePlayer.get())
			{
				TestGame::ThePlayer->Translate({ 0.f, 1.f });
				TestGame::ThePlayer->SetAirTime(0.f);
				TestGame::ThePlayer->AddVelocity(Vec2(0, TestGame::ThePlayer->GetVelocity().Y + newVel));
			}
			else {
				abcgo->GetPhysics()->SetVelocityY(newVel);
			}

		}

		return false;
	}

}
