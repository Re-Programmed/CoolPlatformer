#include "ActiveBoxCollider.h"
#include "../../../Utils/CollisionDetection.h"
#include "PixelPerfectCollider.h"

//The maximum/minimum height that objects can be pushed on top of other objects when colliding with the side of eachother.
#define DAMPING_STEP_HEIGHT_MAX 2.f		
#define DAMPING_STEP_HEIGHT_MIN 0.1f
#define STEP_X_PUSH_MIN 0.1f

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

							//Allow active objects colliding with the side of another static object to be pushed on top of the static object if they're close enough to the top edge of the static object.
							float topEdgeDistance = collider->GetObject()->GetPosition().Y + collider->GetObject()->GetScale().Y - m_object->GetPosition().Y;
							if (topEdgeDistance < DAMPING_STEP_HEIGHT_MAX && topEdgeDistance > DAMPING_STEP_HEIGHT_MIN && push.X > STEP_X_PUSH_MIN)
							{
								push.Y += topEdgeDistance;
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