#pragma once

#include "../../../../Objects/GameObject.h"
#include "../../../../Rendering/Renderers/Renderer.h"
#include "GlitchableObject.h"

#include <map>

namespace GAME_NAME::Objects
{
	class GlitchedRegion
		: public GameObject
	{
	public:

		GlitchedRegion(Vec2 position, Vec2 scale);

		void Update(GLFWwindow* window) override;

		void Render(const Vec2& cameraPosition) override;

	private:
		static int m_spriteCountBeforePixelated;

		static inline GLuint getTextureRelativeGlitched(GLuint textureID)
		{
			return textureID + m_spriteCountBeforePixelated;
		};

		std::unordered_map<GameObject*, Environment::Effects::GlitchableObject*> m_currentlyActiveGlitchables;
	};
}