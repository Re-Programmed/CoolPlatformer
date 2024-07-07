#pragma once

#include "./LightingSource.h"
#include "../Sprite.h"
#include "../../EngineCompileOptions.h"

namespace GAME_NAME::Rendering::Lighting
{
	class SimpleLightingManager
	{
	public:
		/// <summary>
		/// Enables the lighting vertex effect.
		/// Lighting Groups - How many vertical segments to divide the level into when calculating lighting. Used to prevent searching over large numbers of lights by only checking the groups contained in the camera's range. (IT SHOULD BE ENSURED THAT THERE ARE NEVER MORE THAN 3 GROUPS ON SCREEN AT ONCE)
		/// Moving lights will need to be registered as dynamic.
		/// </summary>
		static void EnableLighting(int lightingGroups, bool allowBackgroundLighting = false);

		/// <summary>
		/// Disables the lighting vertex effect.
		/// </summary>
		static void DisableLighting();
		
		/*
			Dynamic light sources are sources that will be crossing over lightingGroups. These should be used for moving lights.
		*/

		/// <summary>
		/// Registers a light source for rendering every frame. (called once, unlike with collisions)
		/// </summary>
		static void RegisterSource(LightingSource* source, bool dynamic = false);
		/// <summary>
		/// Removes a light source from rendering.
		/// </summary>
		static void RemoveSource(LightingSource* source, bool dynamic = false);
	protected:
		/// <summary>
		/// The program to be run on each vertex of each sprite to apply lighting effects.
		/// </summary>
		/// <param name="sprite">[Sprite*] - The sprite to apply to.</param>
		/// <param name="vertex">[Vec2] - The vertex to apply to.</param>
		static void lightingExecution(Sprite* sprite, const Vec2& worldPosition, const Vec2& scale, const float& rotation, VertexData* data);

		/// <summary>
		/// A list of all currently active light sources.
		/// </summary>
		static std::vector<std::vector<LightingSource*>> m_sources;
		static std::vector<LightingSource*> m_dynamicSources;
	private:
		static inline bool m_backgroundLighting = false;

		static int m_vertexExecutionID;

		static inline int getLightingGroupID(float xPosition)
		{
			int groupSize = (DEFAULT_LEVEL_SIZE_X << 6 /*SHOULD BE CHUNK SHIFT*/) / m_sources.size();

			int groupID = (int)(xPosition) % groupSize;

			if (groupID > m_sources.size()) { return m_sources.size() - 1; }
			return groupID;
		};
	};
}