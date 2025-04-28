#pragma once
#include <functional>
#include "../Components/IComponent.h"
#include "../Components/Physics/Collision/StaticCollider.h"
#include "../Utils/Math/Vec2.h"
#include "../Rendering/Renderers/Renderer.h"
#include "../Components/ComponentObject.h"
#include <sstream>
#include "../Resources/AssetManager.h"


namespace GAME_NAME
{
	class Mappings
	{
	public:
		static void LoadObjectsWithDefaultMapping(const char* levelPath);	//Used to map each part of an object.pk file to a GameObject.
		static GameObject* LoadObjectWithDefaultMapping(std::string objectCode);	//Loads a single object based on its object code (0,0,0,01,5,02).

		static void LoadOver20Switch(int index, std::vector<std::string> data, size_t saveIndex);
	};
}