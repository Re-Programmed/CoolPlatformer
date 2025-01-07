#pragma once

#include "../../../../Objects/Particles/ParticleEmitter.h"
#include "../../../../Utils/RemoveableUpdateable.h"

namespace GAME_NAME::Objects::Environment::Effects
{
using namespace Particles;

	class Rain
		: public Utils::RemoveableUpdateable
	{
	public:
		/// <summary>
		/// Creates a rain effect.
		/// </summary>
		static void StartRainEffect();

		void Update(GLFWwindow* window) override;

		/// <summary>
		/// Ends the active rain effect.
		/// </summary>
		/// <param name="freeSpawner"> - deletes the active particle emitter and particles from the level. Should be used if a level is getting reset.</param>
		static void EndRainEffect(bool freeSpawner = false);
	private:

		static Rain* m_loopInstance;

		static ParticleEmitter* m_rainEffect;
	};
}