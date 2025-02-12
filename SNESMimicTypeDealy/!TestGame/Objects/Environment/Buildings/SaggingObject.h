#pragma once
#include "../../../../Objects/GameObject.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	
using namespace Rendering;

	class SaggingObject
		: public GameObject
	{
	public:
		SaggingObject(Vec2 position, Vec2 scale, Sprite* sprite, uint8_t sagSegments);

		void Update(GLFWwindow* window) override;
		void Render(const Vec2& cameraPosition) override;

	private:
		std::vector<GameObject*> m_sagObjects;
	};
}