#pragma once

#include "../../../Objects/GameObject.h"
#include "../../../Objects/GameObjectState.h"

namespace GAME_NAME::Objects::Environment
{
	class ExplosiveObject
		: public GameObject, public GameObjectState
	{
	public:
		enum EXPLOSION_REASON
		{
			JUMPED_ON = 0b00001
		};

		void LoadState() override;
		void SaveState() override;

		/// <summary>
		/// Creates an explosive object.
		/// </summary>
		/// <param name="position"> - where it is.</param>
		/// <param name="scale"> - the scale of the object.</param>
		/// <param name="sprite"> - the sprite.</param>
		/// <param name="explosionRadius"> - the explosion radius parameter for the explosion effect.</param>
		/// <param name="explosionPower"> - the explosion power parameter for the explosion effect.</param>
		/// <param name="sensitivity"> - what can make it explode.</param>
		ExplosiveObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float explosionRadius, float explosionPower, EXPLOSION_REASON sensitivity, size_t saveID);

		void Update(GLFWwindow* window) override;
	private:
		const float m_explosionRadius, m_explosionPower;
		const EXPLOSION_REASON m_reason;

		/// <summary>
		/// Explodes this object.
		/// </summary>
		/// <param name="createExplosion"> - if false, it will just leave the floor mark and delete itself. Setting to false will also not save the current state.</param>
		void explode(bool createExplosion = true);
	};
}