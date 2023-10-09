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
            m_position.X += x;
            m_position.Y += y;
        }

        void GameObject::SetPositionAndScale(Vec2& position, Vec2& scale, Rendering::Sprite* sprite)
        {
            m_position = position;
            m_scale = scale;
            if (sprite != nullptr) { m_sprite = sprite; }
        }

        void GameObject::SetScale(Vec2 scale)
        {
            m_scale = scale;
        }

        Vec2 GameObject::GetScale()
        {
            return m_scale;
        }

        float GameObject::GetRotation()
        {
            return m_rotation;
        }

        Rendering::Sprite* GameObject::GetSprite()
        {
            return m_sprite;
        }

        void GameObject::SetSprite(Rendering::Sprite* sprite)
        {
            m_sprite = sprite;
        }

        GameObject::GameObject() : m_position(Vec2::Zero), m_scale(Vec2::Zero), m_rotation(0.f)
        {

        }

        GameObject::~GameObject()
        {
            //delete m_sprite;
        }

        void GameObject::Render(const Vec2 cameraPosition)
        {
            m_sprite->Render(cameraPosition, m_position + (m_textureFlipped ? (m_scale * Vec2::OneX) : 0), m_scale * (m_textureFlipped ? Vec2::MinusOneX : 1), m_rotation);
        }

    }
}