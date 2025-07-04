#pragma once
#include "../Objects/GameObject.h"
#include "./IComponent.h"
#include "../Utils/Math/Vec2.h"

namespace GAME_NAME
{
	namespace Components
	{
		using namespace MathUtils;

		/// <summary>
		/// An object that can hold components.
		/// </summary>
		class ComponentObject
			: public GAME_NAME::Objects::GameObject
		{
		public:
			ComponentObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite, std::vector<IComponent*> components)
				: GameObject(position, scale, sprite), m_componentCount(static_cast<unsigned int>(components.size())), m_components(components)
			{
				for (unsigned int i = 0; i < components.size(); i++)
				{
					//m_components[i] = components[i];
					m_components[i]->Init(this);
				}
			}

			virtual void Update(GLFWwindow* window)
			{
				for (unsigned int i = 0; i < m_componentCount; i++)
				{
					m_components[i]->Update(window, this);
				}
			}


			~ComponentObject()
			{

			}

			inline IComponent* GetComponent(unsigned int index)
			{
				if (m_components.size() <= index)
				{
					return nullptr;
				}

				return m_components[index];
			}

		private:
			const unsigned int m_componentCount;
			const std::vector<IComponent*> m_components;
		};
	}
}