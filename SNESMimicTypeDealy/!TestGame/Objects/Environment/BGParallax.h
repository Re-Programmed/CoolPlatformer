#pragma once
#include "../../../Objects/GameObject.h"

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			class BGParallax
				: public GameObject
			{

			public:
				BGParallax(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float parallax)
					: GameObject(position, scale, sprite), m_pAmount(parallax)
				{

				}

				void Render(const Vec2 cameraPosition) override
				{
					m_sprite->Render(((Vec2)cameraPosition)/m_pAmount, m_position, m_scale, m_rotation);
				}

			private:
				float m_pAmount;
			};
		}
	}
}