#pragma once

#include "../Objects/GameObject.h"

#if _DEBUG
#include "../Debug/DebugLog.h"
#endif

namespace GAME_NAME::Components
{
	using namespace Objects;

	class ChildGameObject
		: public GameObject
	{
	public:
		ChildGameObject(Vec2 relPosition, Vec2 scale, Rendering::Sprite* sprite, GameObject* parent, float rotation = 0.f) : GameObject(relPosition + parent->GetPosition(), scale, sprite, rotation), m_parent(parent), m_relPosition(relPosition) {};
		ChildGameObject() : m_parent(nullptr), m_relPosition(Vec2(0)) {};

		~ChildGameObject()
		{
			GameObject::~GameObject();
		}

		void Update(GLFWwindow* window) override
		{
			if (m_parent != nullptr)
			{
				m_position = m_parent->GetPosition() + m_relPosition;
				return;
			}

#if _DEBUG
			DEBUG::DebugLog::LogWarning("A ChildGameObject exists with no parent!", true);
#endif
		}

		void SetPosition(Vec2 relPosition)
		{
			m_relPosition = relPosition;
		}
		
		inline Vec2 GetLocalPosition()
		{
			return m_relPosition;
		}

		void Translate(Vec2 translate)
		{
			m_relPosition += translate;
		}

		void Translate(float x, float y)
		{
			m_relPosition.X += x;
			m_relPosition.Y += y;
		}

	protected:
		Vec2 m_relPosition;

		GameObject* const m_parent;

	private:
	};
}