#include "GameObject.h"
namespace GAME_NAME
{

    namespace Objects
    {

        void GameObject::SetPosition(Vec2 position)
        {
            m_position = position;
        }

        Vec2 GameObject::GetPosition()
        {
            return m_position;
        }

        void GameObject::Translate(Vec2 translate)
        {
            SetPosition(m_position + translate);
        }

        void GameObject::Translate(float x, float y)
        {
            m_position.X = x;
            m_position.Y = y;
        }

        void GameObject::SetScale(Vec2 scale)
        {
            m_scale = scale;
        }

        Vec2 GameObject::GetScale()
        {
            return m_scale;
        }

        Rendering::Sprite* GameObject::GetSprite()
        {
            return m_sprite;
        }

        GameObject::GameObject() : m_position(Vec2::Zero), m_scale(Vec2::Zero)
        {

        }

        void GameObject::Render(const Vec2 cameraPosition)
        {
            m_sprite->Render(cameraPosition, m_position, m_scale);
        }

    }
}