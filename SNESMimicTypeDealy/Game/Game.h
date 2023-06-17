#pragma once

#define GLFW_INCLUDE_NONE
#include "../Resources/AssetManager.h"
#include "../Objects/Levels/Data/LevelDataParser.h"
#include "../Rendering/Renderers/Renderer.h"
#include "../Utils/ConstUpdateable.h"
#include "Level.h"
#include "../!TestGame/Camera/GameCamera.h"

#if _DEBUG
#include "../Debug/DebugLog.h"
#endif

namespace GAME_NAME
{
	using namespace Utils;

	namespace Game
	{
		//Stores everything that should happen in Update,Init,LoadLevel,and Late Update.
		class Game : ConstUpdateable
		{
			

		public:
			bool RenderFront = false;	//If true, this will draw the front layer of sprites. Kind of like sprite priority on the Genesis, sprites can be in the front or the middle, front sprites are invisible if this is false.

			//Please make sure to call Update() from game if you override it.
			virtual void Update(GLFWwindow* window)
			{
				LateUpdate(window);
			}
			virtual void Init(GLFWwindow* window) = 0;			//Called on game load.
			virtual void LateUpdate(GLFWwindow* window) = 0;	//Called after rendering.

			/// <summary>
			/// Called when a level is loaded.
			/// </summary>
			/// <param name="level">The level that was loaded.</param>
			virtual void InitLevel(Level level) = 0;

			Rendering::Camera::Camera* GetCamera();

		protected:
			/// <summary>
			/// Used when loading levels to determine what parts of levels to load. Can be combined with BITWISE OR.
			/// </summary>
			enum LEVEL_DATA
			{
				/// <summary>
				/// Everything in the level.
				/// </summary>
				LEVEL_DATA_ALL = 0xFFFFFF,
				/// <summary>
				/// All level music.
				/// </summary>
				LEVEL_DATA_AUDIO_MUSIC = 0x00000F,
				/// <summary>
				/// All level sound effects.
				/// </summary>
				LEVEL_DATA_AUDIO_SFX = 0x0000F0,
				/// <summary>
				/// All level textures.
				/// </summary>
				LEVEL_DATA_TEXTURES_BACKGROUND = 0x000F00,
				/// <summary>
				/// All level sprites/objects.
				/// </summary>
				LEVEL_DATA_TEXTURES_SPRITES = 0x00F000,
				/// <summary>
				/// Level data for chunks and background.
				/// </summary>
				LEVEL_DATA_DATA_CHUNKS = 0x0F0000,
				/// <summary>
				/// Level data file. (level.dat)
				/// </summary>
				LEVEL_DATA_DATA_LEVEL = 0xF0000
			};
			/// <summary>
			/// Load a level from the <u>Assets folder</u>.
			/// 
			/// 
			/// 
			/// <h2>Remember, you must load background textures before sprites.</h2>
			/// </summary>
			/// <param name="levelPath"> -- The folder path to the level.</param>
			/// <param name="data"> -- What data to retrieve from the level.
			/// (ex. Only load the music, or only load the background textures.) 
			/// [Use OR operator to combine fields.]</param>
			/// <param name="reload"> -- If the loaded data should be deleted before its loaded.
			/// (ex. Delete all the current music loaded and populate the AudioPlayer with new music.)
			/// [Does not apply if using <b>LEVEL_DATA_ALL</b>, which must reload]</param>
			void loadLevel(const char* levelPath, LEVEL_DATA data, bool reload = false);

			Rendering::Camera::Camera* m_camera;
		private:
			Level m_level; //The current level.
		};
	}
}