#pragma once

#include "../../../../Objects/GameObject.h"


namespace GAME_NAME::Objects::Environment::Effects
{
	
constexpr int RAND_TEXTURE_RANGE = 100;

	class GlitchEffect
		: public GameObject
	{
	public:
		GlitchEffect(Vec2 position, Vec2 scale);

		void Render(const Vec2& cameraPosition) override;

	private:
		GameObject* m_purples[5];
	};
}