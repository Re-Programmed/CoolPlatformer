#pragma once
#include "../../../Utils/IUpdateable.h"
#include "ActiveCollider.h"
#include "StaticCollider.h"

namespace GAME_NAME
{
	namespace Components
	{
		namespace Physics
		{
			namespace Collision
			{
				class CollisionManager final	//Checks if objects are colliding executes any functions accordingly.
				{
				public:
					/// <summary>
					/// Registers a static collider to be processed this frame.
					/// </summary>
					/// <param name="staticCollider"></param>
					static void RegisterStaticColliderToBuffer(StaticCollider* staticCollider);	//Should be called each frame to register a static collider to a temporary buffer that is calculated on the frame and then deleted.
					/// <summary>
					/// Registers an active collider to be processed this frame.
					/// </summary>
					/// <param name="staticCollider"></param>
					static void RegisterActiveColliderToBuffer(ActiveCollider* activeCollider);	//Should be called each frame to register an active collider to a temporary buffer that is calculated on the frame and then deleted.
					
					/// <summary>
					/// Should be called after objects are updated. (Updates collisions and clears the buffers.)
					/// </summary>
					static void UpdateAndClearBuffers();	//Detects collisions and clears all buffers. Should be called after all updates and all render calls.
				private:
					static std::vector<StaticCollider*> m_staticColliders;
					static std::vector<ActiveCollider*> m_activeColliders;
				};
			}
		}
	}
}