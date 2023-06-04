#pragma once
#include <functional>
#include "../Components/IComponent.h"
#include "../Components/Physics/Collision/StaticCollider.h"
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Renderers/Renderer.h"
#include "../Components/ComponentObject.h"
#include <sstream>
#include "../Resources/AssetManager.h"

#define COMPONENT_MAPPINGS_SIZE 1
#define MAPPINGS_SIZE 4

namespace GAME_NAME
{
	class Mappings
	{
	public:
		static void LoadObjectsWithDefaultMapping(const char* levelPath);
	private:
		static const std::function<Components::IComponent* (std::vector<std::string>)> m_componentMappings[COMPONENT_MAPPINGS_SIZE];
		static std::function<Objects::GameObject* (std::vector<std::string>)> m_mappings[MAPPINGS_SIZE];
	};
}