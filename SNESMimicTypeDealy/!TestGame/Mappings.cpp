#include "Mappings.h"
#include "../Components/Physics/GravityComponent.h"
#include "../Components/Physics/Collision/StaticBoxCollider.h"
#include "../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../Components/Physics/Collision/Helpers/StaticBoxCollisionObject.h"
#include "../Components/Physics/Collision/ActiveBoxCollider.h"
#include "../!TestGame/Objects/Environment/Water.h"
#include "../!TestGame/Objects/Environment/BGParallax.h"
#include "../!TestGame/Objects/Platforms/RotatingPlatform.h"
#include "../Objects/Instantiate/LevelObjectHandler.h"

#include "../!TestGame/Items/FloorItem.h"
#include "../!TestGame/Objects/Environment/Plants/Tree.h"
#include "../!TestGame/Items/Inventories/InventoryContainer.h"

#if _DEBUG
#include "../Debug/DebugLog.h"
#define DebugMapper(x) {std::string s = "[MAPPER] ";DEBUG::DebugLog::Log(s + x, true, ";35");}
#endif

#include "../Components/Physics/Collision/Helpers/PixelPerfectColliderStaticObject.h"
#include "../Objects/Particles/ParticleEmitter.h"

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
constexpr const std::function<Components::IComponent* (std::vector<std::string>)> m_componentMappings[COMPONENT_MAPPINGS_SIZE]
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
constexpr std::function<void (std::vector<std::string>, size_t line)> m_mappings[MAPPINGS_SIZE]
{
	//Basic Object
	[](std::vector<std::string> data, size_t n) {

#if _DEBUG
		DebugMapper(">>> Loading Basic Object");
#endif
		Renderer::LoadObject(new Objects::GameObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))), (data.size() > 5) ? std::stoi(data[5]) : 1U, (data.size() > 6) ? std::stoi(data[6]) > 0 : false);
	},

	//Component Object
	[](std::vector<std::string> data, size_t n)
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
	[](std::vector<std::string> data, size_t n) {

#if _DEBUG
		DebugMapper(">>> Loading StaticBoxCollisionObject");
#endif
		std::cout << "GOT: " << std::stoi(data[4]) << std::endl;
		Renderer::LoadObject(new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))));
	},

	//ActiveBoxCollisionGravityObject
	[](std::vector<std::string> data, size_t n) {

#if _DEBUG
		DebugMapper(">>> Loading ActiveBoxCollisionGravityObject");
#endif
		Renderer::LoadActiveObject(new GAME_NAME::Components::Physics::Collision::ActiveBoxCollisionGravityObject(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4]))));
	},

	//Water
	[](std::vector<std::string> data, size_t n) {

#if _DEBUG
		DebugMapper(">>> Loading Water");
#endif
		Renderer::LoadActiveObject(new GAME_NAME::Objects::Environment::Water(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3])), 1);
	},

	[](std::vector<std::string> data, size_t d)
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

	},

	//GAME
	//BGParallaxObject
	[](std::vector<std::string> data, size_t n) {

#if _DEBUG
		DebugMapper(">>> Loading ParallaxBGObject");
#endif
		Renderer::LoadActiveObject(new GAME_NAME::Objects::Environment::BGParallax(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])), static_cast<float>(std::stoi(data[5])/100.f)), 0);
	},

	/*
		7: Rotating Platform (map,layer,positionX,positionY,scaleX,scaleY,sprite,originX,originY,speed*10,offset*pi/6)
		- A platform that rotates about a fixed point.
	*/
	[](std::vector<std::string> data, size_t n) {
#if _DEBUG
		DebugMapper(">>> Loading RotatingPlatform");
#endif
		Renderer::LoadObject(new GAME_NAME::Objects::Platforms::RotatingPlatform(
			STOIVEC(data[1], data[2]),								//positionX,positionY
			STOIVEC(data[3], data[4]),								//scaleX,scaleY
			Renderer::GetSprite(std::stoi(data[5])),				//sprite
			STOIVEC(data[6], data[7]),								//originX,originY
			static_cast<double>(std::stoi(data[8]) / 10.0),			//speed*10
			M_PI * static_cast<double>(std::stoi(data[9]) / 6.0)	//offset * pi/6
			), std::stoi(data[0]));									//layer
		},

	/*
		8: Floor Item (map,positionX,positionY,itemType)
		- An item that can be picked up.
	*/
	[](std::vector<std::string> data, size_t n)
	{
#if _DEBUG
			DebugMapper(">>> Loading FloorItem(" + data[2] + ")");
#endif
			using namespace GAME_NAME::Items;
			InventoryItem invItem = InventoryItem((ITEM_TYPE)std::stoi(data[2]));
			FloorItem* newFloorItem = new FloorItem(STOIVEC(data[0], data[1]), invItem);

			Renderer::LoadActiveObject(newFloorItem);
	},

	/*
		9: Particle Emitter (map, positionX,positionY,particleLifetime*100,numParticles, particle_1_objparent, particle_1_objname, ...)
	*/
	[](std::vector<std::string> data, size_t n)
	{
#if _DEBUG
		DebugMapper(">>> Loading ParticleEmitter");
#endif 

		using namespace Particles;

		ParticleEmitter pe = ParticleEmitter(STOIVEC(data[1], data[2]), static_cast<float>(std::stoi(data[3]))/100.f);

		for (int i = 4; i < data.size(); i += 2)
		{
			pe.RegisterParticle(Particle(Instantiate::LevelObjectHandler::GetLevelObject(data[i], data[i + 1])));
			Renderer::DestroyObject(Renderer::GetLastLoadedObject());
		}
	},

	/*
		10: Tree (map,positionX,positionY,scaleX,scaleY,sprite,chopSprite,layer)
	*/

	[](std::vector<std::string> data, size_t n)
	{
		Environment::Plants::Tree* tree = new Environment::Plants::Tree(STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])), n, Renderer::GetSprite(std::stoi(data[5])));
		Renderer::LoadActiveObject(tree, std::stoi(data[6]));
	},

	/*
		11: Container Inventory (map,positionX,positionY,scaleX,scaleY,sprite,inventoryName,inventorySize,inventoryItems_Ids...)
	*/
	[](std::vector<std::string> data, size_t n)
	{
		Items::Inventories::InventoryContainer* container = new Items::Inventories::InventoryContainer(data[5], std::stoi(data[6]), STOIVEC(data[0], data[1]), STOIVEC(data[2], data[3]), Renderer::GetSprite(std::stoi(data[4])));
	}
};

void GAME_NAME::Mappings::LoadObjectsWithDefaultMapping(const char* levelPath)
{
#if _DEBUG
	DebugMapper("!=== LOADING OBJECT DATA ===!");
#endif
	Resources::AssetManager::LoadObjectData(levelPath, m_mappings);
}

GameObject* GAME_NAME::Mappings::LoadObjectWithDefaultMapping(std::string objectCode)
{
	Resources::AssetManager::loadObjectDataThread(objectCode, 0, m_mappings);
	return Renderer::GetLastLoadedObject();
}
