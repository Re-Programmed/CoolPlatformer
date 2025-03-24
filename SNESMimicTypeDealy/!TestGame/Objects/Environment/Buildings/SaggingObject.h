#pragma once
#include "../../../../Objects/GameObject.h"
#include "../../../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"
#include "../../../../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	
using namespace Rendering;

	class SaggingObject
		: public GameObject
	{
	public:
		SaggingObject(Vec2 position, Vec2 scale, Sprite* sprite, uint8_t sagSegments, bool bouncy = false);

		void Update(GLFWwindow* window) override;
		void Render(const Vec2& cameraPosition) override;

	private:
		class SaggingSegment
			: public Components::Physics::Collision::StaticBoxCollisionObject
		{
		public:
			SaggingSegment(Vec2 position, Vec2 scale, Sprite* sprite, SaggingSegment* const leftSag)
				: Components::Physics::Collision::StaticBoxCollisionObject(position, scale, sprite, Vec2{scale.X, 7.f /*How tall the collider is underneath the texture.*/}), LeftSag(leftSag)
			{

			};

			SaggingSegment* const LeftSag;
			SaggingSegment* RightSag;

			GameObject* PreventUnsag;
			bool PreventUnsagDirection;

			float PreviousSag;

			float UnsagDelay;

			int IsColliding;


		};

		bool m_isBouncy; uint8_t m_bounceTimer;


		std::vector<SaggingSegment*> m_sagObjects;

		static void saggingObjectBeforeCollision(GameObject* self);
		static bool saggingObjectCollisionEvent(Vec2 push, GameObject* self, GameObject* other);
	};
}