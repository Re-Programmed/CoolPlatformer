#include "Mappings.h"
#include "../Components/Physics/GravityComponent.h"
#include "../Components/Physics/Collision/StaticBoxCollider.h"
#include "../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"
#include "../Components/Physics/Collision/ActiveBoxCollider.h"
#include "../!TestGame/Objects/Environment/Water.h"

#if _DEBUG
#include "../Debug/DebugLog.h"
#define DebugMapper(x) {std::string s = "[MAPPER] ";DEBUG::DebugLog::Log(s + x, true, ";35");}
#endif

#include "../Components/Physics/Collision/Helpers/PixelPerfectColliderStaticObject.h"

constexpr int8_t GenesisTileSize = 8;

inline Vec2 STOIVEC(std::string x, std::string y)
{
	float xcoord, ycoord;
	if (x.ends_with("t"))
	{
		xcoord = std::stoi(x.erase(x.length() - 1)) * GenesisTileSize;
	}
	else { xcoord = std::stoi(x); }

	if (y.ends_with("t"))
	{
		ycoord = std::stoi(y.erase(y.length() - 1)) * GenesisTileSize;
	}
	else { ycoord = std::stoi(y); }

	return GAME_NAME::MathUtils::Vec2(xcoord, ycoord);
}

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
/// Takes in a string vector and spawns a GameObject.
/// </summary>
std::function<void (std::vector<std::string>)> Mappings::m_mappings[MAPPINGS_SIZE]
{
	//Basic Object
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading Basic Object");
#endif
		Renderer::LoadObject(new Objects::GameObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))));
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

		Renderer::LoadObject(new Components::ComponentObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])), components));
	},

	//StaticBoxCollisionObject
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading StaticBoxCollisionObject");
#endif
		Renderer::LoadObject(new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))));
	},

	//ActiveBoxCollisionGravityObject
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading ActiveBoxCollisionGravityObject");
#endif
		Renderer::LoadActiveObject(new GAME_NAME::Components::Physics::Collision::ActiveBoxCollisionGravityObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))));
	},

	//Water
	[](std::vector<std::string> data) {

#if _DEBUG
		DebugMapper(">>> Loading Water");
#endif
		Renderer::LoadActiveObject(new GAME_NAME::Objects::Environment::Water(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3])), 0);
	},

	[](std::vector<std::string> data) 
	{

#if _DEBUG
		DebugMapper(">>> Loading PixelColliderOPbject");
#endif
	    using namespace GAME_NAME::Components::Physics::Collision;
		using namespace GAME_NAME::Components::Physics::Collision::Helpers;
		
		constexpr PixelPerfectCollider::PIXEL_COLLISION_FACE n = PixelPerfectCollider::PIXEL_COLLISION_FACE_NONE;
		constexpr PixelPerfectCollider::PIXEL_COLLISION_FACE t = PixelPerfectCollider::PIXEL_COLLISION_FACE_TOP;
		constexpr PixelPerfectCollider::PIXEL_COLLISION_FACE l = PixelPerfectCollider::PIXEL_COLLISION_FACE_LEFT;
		constexpr PixelPerfectCollider::PIXEL_COLLISION_FACE b = PixelPerfectCollider::PIXEL_COLLISION_FACE_BOTTOM;

		PixelPerfectCollider::PIXEL_COLLISION_FACE collisionFaces[PixelColliderSize * PixelColliderSize] {
			l,b,b,b,b,b,b,b,b,b,b,b,b,b,t,t,
			l,l,b,b,b,b,b,b,b,b,b,t,t,t,t,n,
			l,l,l,b,b,b,b,b,b,b,t,t,t,t,n,n,
			l,l,l,l,b,b,b,b,b,t,t,t,t,n,n,n,
			l,l,l,l,l,b,b,t,t,t,t,t,n,n,n,n,
			l,l,l,l,l,t,t,t,t,t,t,n,n,n,n,n,
			l,l,l,l,l,t,t,t,t,t,n,n,n,n,n,n,
			l,l,l,l,t,t,t,t,t,n,n,n,n,n,n,n,
			l,l,l,l,t,t,t,t,n,n,n,n,n,n,n,n,
			l,l,l,t,t,t,t,n,n,n,n,n,n,n,n,n,
			l,l,t,t,t,t,n,n,n,n,n,n,n,n,n,n,
			l,t,t,t,t,n,n,n,n,n,n,n,n,n,n,n,
			t,t,t,t,n,n,n,n,n,n,n,n,n,n,n,n,
			t,t,t,n,n,n,n,n,n,n,n,n,n,n,n,n,
			t,t,n,n,n,n,n,n,n,n,n,n,n,n,n,n,
			t,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n
		};

		PixelPerfectColliderStaticObject* ppcso = new PixelPerfectColliderStaticObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])), collisionFaces);

		Renderer::LoadObject(ppcso, false);

	}
};

void GAME_NAME::Mappings::LoadObjectsWithDefaultMapping(const char* levelPath)
{
#if _DEBUG
	DebugMapper("!=== LOADING OBJECT DATA ===!");
#endif
	Resources::AssetManager::LoadObjectData(levelPath, m_mappings);
}
