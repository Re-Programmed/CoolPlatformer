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
							//Check if the static collider has anything that needs to happen when it collides.
							if (collider->OnCollision != nullptr)
							{
								if (!(collider->OnCollision)(push, collider->GetObject(), m_object))
								{
									return;
								}
							}

							//Push the objects apart.
							m_object->Translate(push);

							//Check if the active collider has anything that needs to happen when it collides.
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