#include "../StaticBoxCollider.h"
#include "../CollisionManager.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				using namespace MathUtils;

				class StaticBoxCollisionObject		//A collision object that will not be affected by collisions. (ex. The ground, it still collides but it does nothing when it collides.)
					: public Objects::GameObject
				{
				public:
					StaticBoxCollisionObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite)
						: GameObject(position, scale, sprite), m_boxCollider(new StaticBoxCollider())
					{
						m_boxCollider->Init(this);
					}

					~StaticBoxCollisionObject()
					{
						delete m_boxCollider;
					}

					void Update(GLFWwindow* window)
					{
						CollisionManager::RegisterStaticColliderToBuffer(m_boxCollider);
					}

				private:
					StaticBoxCollider* const m_boxCollider;
				};
			}
		}
	}
}