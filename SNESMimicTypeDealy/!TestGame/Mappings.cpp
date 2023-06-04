#include "Mappings.h"
#include "../Components/Physics/GravityComponent.h"
#include "../Components/Physics/Collision/StaticBoxCollider.h"
#include "../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"
#include "../Components/Physics/Collision/ActiveBoxCollider.h"
#include "Objects/DebugObject.h"
#if _DEBUG
#include "../Debug/DebugLog.h"
#define DebugMapper(x) {std::string s = "[MAPPER] ";DEBUG::DebugLog::Log(s + x, true, ";35");}
#endif

#define STOIVEC(x, y) (GAME_NAME::MathUtils::Vec2(std::stoi(x), std::stoi(y)))

using namespace GAME_NAME;

/// <summary>
/// Maps a string array to a component. The first value in the inputted string array is the component type so it can be ignored.
/// </summary>
const std::function<Components::IComponent* (std::vector<std::string>)> Mappings::m_componentMappings[COMPONENT_MAPPINGS_SIZE]
{
	//Example template
	[](std::vector<std::string> componentData) {
#if _DEBUG
			DebugMapper("L [COMPONENTS] Loading Static BOX Collider...");
#endif
		return (Components::IComponent*)(new Components::Physics::Collision::StaticBoxCollider());
	}
};

/// <summary>
/// Takes in a string vector and returns a GameObject.
/// </summary>
std::function<Objects::GameObject* (std::vector<std::string>)> Mappings::m_mappings[MAPPINGS_SIZE]
{
	//Basic Object
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading Basic Object");
#endif
		return new Objects::GameObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])));
	},

	//Component Object
	[](std::vector<std::string> data)
	{
#if _DEBUG
			DebugMapper(">>> Loading Component Object");
#endif
		std::vector<Components::IComponent*> components;
		for (int i = 5; i < data.size(); i++)
		{
			std::stringstream ss(data[i]);
			std::string var;
			std::vector<std::string> out;

			while (std::getline(ss, var, '|'))
			{
				out.push_back(var);
			}

			components.push_back(m_componentMappings[std::stoi(out[0])](out));
		}

		return new Components::ComponentObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])), components);
	},

	//StaticBoxCollisionObject
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading StaticBoxCollisionObject");
#endif
		return new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])));
	},

	//ActiveBoxCollisionGravityObject
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading ActiveBoxCollisionGravityObject");
#endif
		return new GAME_NAME::Components::Physics::Collision::ActiveBoxCollisionGravityObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])));
	}
};

void GAME_NAME::Mappings::LoadObjectsWithDefaultMapping(const char* levelPath)
{
#if _DEBUG
	DebugMapper("!=== LOADING OBJECT DATA ===!");
#endif
	Resources::AssetManager::LoadObjectData(levelPath, m_mappings);
}
