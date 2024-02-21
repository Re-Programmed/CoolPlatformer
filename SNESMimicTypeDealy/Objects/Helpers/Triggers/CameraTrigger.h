#pragma once

#include "../Trigger.h"
#include "../../../!TestGame/Camera/GameCamera.h"

namespace GAME_NAME::Objects
{
	class CameraTrigger
		: public Trigger, public GameObject
	{
	public:
		inline void Callback(uint16_t callCount)
		{
			TestGame::INSTANCE->GetCamera()->SetZoom(m_zoom);
			GAME_NAME::Camera::GameCamera* gc = static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera());
			gc->SetFollowPlayerExact(m_setFollow);
		}

		CameraTrigger(Vec2 position, Vec2 scale, float zoom, bool setFollow = false)
			: GameObject(position, scale, nullptr, 0.0F), Trigger(position, scale, Callback), m_zoom(zoom), m_setFollow(setFollow)
		{

		}

	private:
		const float m_zoom;
		const bool m_setFollow;
	};
}