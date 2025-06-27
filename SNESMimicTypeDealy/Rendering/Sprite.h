#pragma once
#include "../glad/include/glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "../Utils/Math/Vec2.h"
#include "../Utils/Math/Vec4.h"
#include "Camera/Camera.h"

#include <functional>

namespace GAME_NAME
{
	constexpr static float TargetResolutionX = 320.f, TargetResolutionY = 180.f; //Resolution to scale sprites by.

	namespace Rendering
	{
		using namespace MathUtils;

		/// <summary>
		/// Gets pushed to each prerender execution to tell what has already been updated.
		/// </summary>
		struct VertexData
		{
			Vec2 Position; bool PositionSet;
			Vec2 TextureCoordinate; bool TextureCoordSet;
			Vec4 Color; bool ColorSet;

			VertexData(Vec2 position, Vec2 textureCoord)
				: Position(position), TextureCoordinate(textureCoord), Color(1.f, 1.f, 1.f, 1.f), PositionSet(false), TextureCoordSet(false), ColorSet(false)
			{

			}

			VertexData()
				: Position(Vec2::Zero), TextureCoordinate(Vec2::Zero), Color(1.f, 1.f, 1.f, 1.f), PositionSet(false), TextureCoordSet(false), ColorSet(false)
			{

			}

			/// <summary>
			/// Set the vertex position.
			/// Ensures that if another prerender effect has modified this parameter it will not be modified.
			/// </summary>
			/// <param name="color">[Vec2] - Vertex Position.</param>
			inline void SetPosition(Vec2 position)
			{
				if (!PositionSet)
				{
					Position = position;
					PositionSet = true;
				}
			}

			/// <summary>
			/// Set the texture coordinate.
			/// Ensures that if another prerender effect has modified this parameter it will not be modified.
			/// </summary>
			/// <param name="color">[Vec2] - Texture Coordinate.</param>
			inline void SetTextureCoordiante(Vec2 coordinate)
			{
				if (!TextureCoordSet)
				{
					TextureCoordinate = coordinate;
					TextureCoordSet = true;
				}
			}

			/// <summary>
			/// Set the color.
			/// Ensures that if another prerender effect has modified this parameter it will not be modified.
			/// </summary>
			/// <param name="color">[Vec4] - Vertex Color.</param>
			inline void SetColor(Vec4 color)
			{
				if (!ColorSet)
				{
					Color = color;
					ColorSet = true;
				}
			}
		};

		class Sprite	//Something drawn to the screen.
		{
		public:
			Sprite(const unsigned int spriteId) : m_spriteId(spriteId) {};								//spriteId should be the sprites buffer id. Sprites are loaded based on their position in the sprites directory.
			virtual void Render(const Vec2 cameraPosition, Vec2 position, Vec2 scale, float rotation = 0.f);	//Render should be called to render a sprite to the screen.

#if _DEBUG
			//DEBUG
			inline std::string ToString()																//DEBUGGING
			{
				return "Sprite {" + std::to_string(this->m_spriteId) + "}";
			}
#endif

			/// <summary>
			///  *** Should only really be used by prerender executions hoping to modify the sprite before it is rendered. If a new sprite should be drawn to the screen, a new Sprite() should be created.
			/// </summary>
			inline void SetSpriteId(unsigned int id)
			{
				m_spriteId = id;
			}

			static void SetResolution(Vec2 res);														//Sets the resolution scale of all sprites. This determines how to scale the sprites based on the resizing of the window. [Maintains scale no matter your resolution]

			const unsigned int GetSpriteId();															//Returns the sprite buffer index currently used.

			/// <summary>
			/// Registers a function to be called on each vertex of this sprite. (like a vertex shader)
			/// This function can do stuff like apply lighting and other effects.
			/// </summary>
			/// <param name="prerenderExecution">[std::function<void(Sprite* sprite, Vec2 vertex)>] - The functio to call on the vertex.</param>
			/// <returns></returns>
			static unsigned int AddPrerenderExecution(std::function<void(Sprite*, const Vec2&, const Vec2&, const float&, VertexData*)> prerenderExecution);

			/*
				Prerender Executions are used to update certain vertex data using the VertexData pointer.
				Executions can use the vertexdata booleans to ensure they are never overriding each other, or they can just override the other effects.				

				Sprite* is used to get details about what sprite is actually getting rendered.
				Vec2 is used to pass the object world position.
				VertexData is the variable modified by executions that is acually used during rendering.
			 */

		protected:
			/// <summary>
			/// Functions to be called on each vertex.
			/// </summary>
			static std::vector<std::function<void(Sprite*, const Vec2&, const Vec2&, const float&, VertexData*)>> m_prerenderExecutions;

			static Vec2 m_resolutionScale;																//Resolution scale of all sprites.

			 unsigned int m_spriteId;																//Current sprite buffer ID.
		};
	}
}