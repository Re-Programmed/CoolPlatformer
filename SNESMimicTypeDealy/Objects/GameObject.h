#pragma once
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Sprite.h"
#include "../Rendering/Camera/Camera.h"
namespace GAME_NAME
{

	namespace Objects
	{
		using namespace MathUtils;
		class GameObject	//An object in game. Stores a position, scale, rotation, and sprite.
		{
		public:
			void SetPosition(Vec2 position);
			Vec2 GetPosition();
			void Translate(Vec2 translate);			//Move the object's position.
			void Translate(float x, float y);		//Move the object's position.

			void SetPositionAndScale(Vec2& position, Vec2& scale, Rendering::Sprite* sprite = nullptr);	//Allows the setting of the position, scale, and sprite all in one! 

			void SetScale(Vec2 scale);
			Vec2 GetScale();

			float GetRotation();

			/// <summary>
			/// Rotates an object around its center point by adjusting its position. IN DEGREES
			/// </summary>
			/// <param name="rotation">How much to rotate by.</param>
			void RotateAboutCenter(float rotation);
			void SetRotationAboutCenter(float rotation);

			Rendering::Sprite* GetSprite();
			void SetSprite(Rendering::Sprite* sprite);
			
			/// <summary>
			/// Flips the texture accross the Y axis.
			/// </summary>
			/// <param name="textureFlipped"></param>
			inline void SetTextureFlipped(bool textureFlipped)
			{
				m_textureFlipped = textureFlipped;
			}

			inline bool GetTextureFlipped()
			{
				return m_textureFlipped;
			}

			GameObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float rotation = 0.f) : m_position(position), m_sprite(sprite), m_scale(scale), m_rotation(rotation), m_rotationOffset(0), m_textureFlipped(false) {};


			GameObject();

			~GameObject();

			virtual void Render(const Vec2& cameraPosition);

			virtual void Update(GLFWwindow* window)
			{

			}

		protected:
			Vec2 m_position;
			Vec2 m_scale;
			Rendering::Sprite* m_sprite;
			float m_rotation;

			bool m_textureFlipped;

		private:
			Vec2 m_rotationOffset;

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