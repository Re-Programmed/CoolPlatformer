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

				class StaticBoxCollisionObject
					: public Objects::GameObject
				{
				public:
					StaticBoxCollisionObject(Vec2 position, Vec2 scale, GAME_NAME::Rendering::Sprite* sprite)
						: GameObject(position, scale, sprite), m_boxCollider(new StaticBoxCollider())
					{
						CollisionManager::InitStaticCollider(m_boxCollider);
						m_boxCollider->Init(this);
					}

					~StaticBoxCollisionObject()
					{
						delete m_boxCollider;
					}

				private:
					StaticBoxCollider* const m_boxCollider;
				};
			}
		}
	}
}