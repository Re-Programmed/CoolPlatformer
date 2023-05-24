#pragma once
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Camera/Camera.h"
namespace GAME_NAME
{

	namespace Objects
	{
		using namespace MathUtils;
		class GameObject
		{
		public:
			void SetPosition(Vec2 position);
			Vec2 GetPosition();

			void SetScale(Vec2 scale);
			Vec2 GetScale();

			Rendering::Sprite* GetSprite();

			GameObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite) : m_position(position), m_sprite(sprite), m_scale(scale) {};
			GameObject();

			void Render(const Vec2 cameraPosition);
		private:
			Vec2 m_position;
			Vec2 m_scale;
			Rendering::Sprite* m_sprite;
		};
	}
}