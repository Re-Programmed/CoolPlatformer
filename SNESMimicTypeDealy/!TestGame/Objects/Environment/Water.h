#pragma once
#include "../../../Objects/GameObject.h"
#include "../../../Rendering/DynamicSprite.h"
#include <vector>
#include <memory>

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			typedef struct BakedReflection {		//Baked reflection stores an object and a DynamicSprite that can be updated to apply ripples to reflections.
				GameObject Object;
				std::unique_ptr<Rendering::DynamicSprite> Sprite;

				Vec4 Perc;
				float Check;
			};

			constexpr int8_t WaterSprite = 37;	//Default sprite for water to use.
			/// <summary>
			/// Water GameObjects.
			/// </summary>
			class Water
				: public GameObject
			{
			public:
				/// <summary>
				/// 
				/// </summary>
				/// <param name="position">The position of the water.</param>
				/// <param name="scale">The scale of the water.</param>
				Water(Vec2 position, Vec2 scale);

				/// <summary>
				/// Update to be called every frame to update reflections and check if the player should be swimming.
				/// </summary>
				/// <param name="window"></param>
				void Update(GLFWwindow* window);
			private:
				std::vector<std::unique_ptr<BakedReflection>> m_bakedReflections;	//Array of objects that are displayed as reflections of objects above the water. Calculated on level load.

				const Vec2 m_reflectionPosition;									//The line at which objects should be relfected accross vertically. (The top of the water)

				bool m_playerIn = false;											//If the player is in this water object.
				void checkPlayerIn();												//Called to determine if the player is in this water. (Should be called on update or when the player moves.)
			};
		}
	}
}