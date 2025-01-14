#pragma once

#include "../../../Objects/GameObject.h"

namespace GAME_NAME::Objects::Environment
{
	class ExplosiveObject
		: public GameObject
	{
	public:
		enum EXPLOSION_REASON
		{
			JUMPED_ON = 0b00001
		};

		/// <summary>
		/// Creates an explosive object.
		/// </summary>
		/// <param name="position"> - where it is.</param>
		/// <param name="scale"> - the scale of the object.</param>
		/// <param name="sprite"> - the sprite.</param>
		/// <param name="explosionRadius"> - the explosion radius parameter for the explosion effect.</param>
		/// <param name="explosionPower"> - the explosion power parameter for the explosion effect.</param>
		/// <param name="sensitivity"> - what can make it explode.</param>
		ExplosiveObject(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, float explosionRadius, float explosionPower, EXPLOSION_REASON sensitivity);

		void Update(GLFWwindow* window) override;
	private:
		const float m_explosionRadius, m_explosionPower;
		const EXPLOSION_REASON m_reason;

		void explode();
	};
}