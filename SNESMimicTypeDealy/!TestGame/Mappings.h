#pragma once
#include <functional>
#include "../Components/IComponent.h"
#include "../Components/Physics/Collision/StaticCollider.h"
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Renderers/Renderer.h"
#include "../Components/ComponentObject.h"
#include <sstream>
#include "../Resources/AssetManager.h"

#define COMPONENT_MAPPINGS_SIZE 1	//How many component mappings there are
#define MAPPINGS_SIZE 9				//How many object mappings there are.

namespace GAME_NAME
{
	class Mappings
	{
	public:
		static void LoadObjectsWithDefaultMapping(const char* levelPath);	//Used to map each part of an object.pk file to a GameObject.
	private:
		static const std::function<Components::IComponent* (std::vector<std::string>)> m_componentMappings[COMPONENT_MAPPINGS_SIZE];	//Stores what integers refer to what components for component objects.
		static std::function<void (std::vector<std::string>)> m_mappings[MAPPINGS_SIZE];												//Stores a list of conversions from a string to a GameObject. The conversion called is based on the first integer in each string of an object.pk file.
	};
}