#include "ActiveBoxCollider.h"
#include "../../../Utils/CollisionDetection.h" 


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

				}

				void ActiveBoxCollider::CheckActiveCollisionShapes(ActiveCollider* collider)
				{

				}
			}
		}
	}
}