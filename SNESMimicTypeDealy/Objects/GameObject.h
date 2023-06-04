#pragma once
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Camera/Camera.h"
namespace GAME_NAME
{

#define LAYER_COUNT 3

	typedef int Layer;

	namespace Objects
	{
		using namespace MathUtils;
		class GameObject
		{
		public:
			void SetPosition(Vec2 position);
			Vec2 GetPosition();
			void Translate(Vec2 translate);
			void Translate(float x, float y);

			void SetScale(Vec2 scale);
			Vec2 GetScale();

			Rendering::Sprite* GetSprite();

			GameObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, Layer m_layer) : m_position(position), m_sprite(sprite), m_scale(scale) {};
			GameObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite) : m_position(position), m_sprite(sprite), m_scale(scale), m_layer(1) {};
			GameObject();

			void Render(const Vec2 cameraPosition);

			virtual void Update(GLFWwindow* window)
			{

			}
			
			virtual bool GetActive()
			{
				return false;
			}

			Layer GetLayer()
			{
				return m_layer;
			}

		private:
			Vec2 m_position;
			Vec2 m_scale;
			Rendering::Sprite* m_sprite;

			Layer m_layer;
		};
		/*
		class GameObjectMapping
			: public IObjectComponentMapping
		{
		public:
			Objects::GameObject* FromMapping(std::vector<std::string> inputs)
			{
				return new GameObject(Vec2(std::stoi(inputs[1]), std::stoi(inputs[2])), Vec2(std::stoi(inputs[3]), std::stoi(inputs[4])), new Sprite(std::stoi(inputs[5])));
			}
		};*/
	}
}