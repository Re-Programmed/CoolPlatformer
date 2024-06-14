#pragma once
#include "../../../../Objects/GameObject.h"
#include <memory>

namespace GAME_NAME::Objects::Environment::Buildings
{
	struct BuildingZone
	{
		const Vec2 Position;
		const Vec2 Scale;

		BuildingZone(const Vec2 pos, const Vec2 sca) : Position(pos), Scale(sca) {}
	};

	class FrontWall
		: public GameObject
	{
	public:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="position">The position of the wall.</param>
		/// <param name="scale">The scale of the wall.</param>
		/// <param name="sprite">The sprite of the wall.</param>
		/// <param name="baseOpacity">The opacity of the wall when it should be displayed.</param>
		FrontWall(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, std::shared_ptr<BuildingZone> buildingZone, float baseOpacity = 1.f);

		void Render(const Vec2& cameraPosition) override;

		void Update(GLFWwindow* window) override;

		~FrontWall();
	private:
		/// <summary>
		/// Represents the opacity of the wall when it should be displayed.
		/// </summary>
		float m_baseOpacity;
		/// <summary>
		/// True if the wall is currently hidden.
		/// </summary>
		bool m_isClear;

		/// <summary>
		/// The current opacity of the wall.
		/// </summary>
		float m_opacity = 1.f;

		const std::shared_ptr<BuildingZone> m_buildingZone;
	};
}