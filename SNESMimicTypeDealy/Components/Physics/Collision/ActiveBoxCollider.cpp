#include "ActiveBoxCollider.h"
#include "../../../Utils/CollisionDetection.h"
#include "PixelPerfectCollider.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				void ActiveBoxCollider::Update(GLFWwindow* window, Objects::GameObject* object)
				{

				}

				void ActiveBoxCollider::CheckStaticCollisionShapes(StaticCollider* collider)
				{
					//Detection for box hitting box.
					if (instanceof<StaticBoxCollider>(collider))
					{
						Vec2 push = Vec2::Zero;
						if (Utils::CollisionDetection::BoxWithinBox(m_object->GetPosition(), m_object->GetScale(), collider->GetObject()->GetPosition(), collider->GetObject()->GetScale(), push))
						{
							m_object->Translate(push);

							if (m_onCollision != nullptr)
							{
								(m_onCollision)(push, m_object);
							}
						}
					}
					//Detection for box hitting pixel perfect collider.
					else if(instanceof<PixelPerfectCollider>(collider)) {
						
						PixelPerfectCollider* col = static_cast<PixelPerfectCollider*>(collider);
						Vec2 push = Vec2::Zero;
						//Check if we are inside the bounding box of the pixel perfect collider.
						if (Utils::CollisionDetection::BoxWithinBox(m_object->GetPosition(), m_object->GetScale(), collider->GetObject()->GetPosition(), collider->GetObject()->GetPosition(), push))
						{
							//Get our offset from the bottom corner of the object.
							Vec2 offset = m_object->GetPosition() - collider->GetObject()->GetPosition();

							Vec2 scalar = Vec2(PixelColliderSize / collider->GetObject()->GetScale().X, PixelColliderSize / collider->GetObject()->GetScale().Y);

							offset = (offset * scalar);

							offset.Clamp(0.f, PixelColliderSize, 0.f, PixelColliderSize);

							std::cout << offset.ToString() << std::endl;

							switch (col->CheckPixel(offset))
							{
							case PixelPerfectCollider::PIXEL_COLLISION_FACE_BOTTOM:
								push = Vec2(0, -1);
								break;
							case PixelPerfectCollider::PIXEL_COLLISION_FACE_TOP:
								push = Vec2(0, 1);
								break;
							case PixelPerfectCollider::PIXEL_COLLISION_FACE_LEFT:
								push = Vec2(-1, 0);
								break;
							case PixelPerfectCollider::PIXEL_COLLISION_FACE_RIGHT:
								push = Vec2(0, 1);
								break;
							case PixelPerfectCollider::PIXEL_COLLISION_FACE_NONE:
								return;
							default:
								return;
							}

							m_object->Translate(push);
							if (m_onCollision != nullptr)
							{
								(m_onCollision)(push, m_object);
							}
						}
					}
				}

				void ActiveBoxCollider::CheckActiveCollisionShapes(ActiveCollider* collider)
				{

				}
			}
		}
	}
}