#pragma once
#include "../glad/include/glad/glad.h"
#include <iostream>
#include <filesystem>
#include "../Objects/Levels/Data/LevelDataParser.h"
#include "../Objects/GameObject.h"
#include <functional>

constexpr const char* AssetPath = "./Assets";			//Path to the Asset folder that contains all level data.
constexpr const char* SpriteSubfolder = "/sprite";		//Path within a level to its sprites.
constexpr const char* BGSubfolder = "/bg";				//Path within a level to its background sprites.

constexpr const char* MenuSubfolder = "/Menus";			//Path within assets to the folder containing menus.

constexpr const char* ChunkFileName = "/chunk.pk";		//Path within a level to its chunk.pk file.
constexpr const char* LevelFileName = "/level.dat";		//Path within a level to its level.dat file.
constexpr const char* ObjectFileName = "/object.pk";	//Path within a level to its object.pk file.

constexpr const char* MenuFileExtension = ".pk";		//Extension for menu files.

constexpr const char* MusicFilePath = "/music";			//Path within a level to its music folder.

///!Max number of texture assets to store at one time. [------- CURRENTLY NOT USED; HOWEVER, MAYBE USE A RENDER LIMIT OF 80 SPRITES WITH 20 ON EACH SCANLINE FOR RETRONESS. -------]
#define ASSET_LIMIT 50

enum TEXTURE_LOAD
{
	ALL_TEXTURES = 0,
	SPRITES = 1,
	BACKGROUND = 2
};

namespace GAME_NAME
{

	namespace Resources
	{
		//Loads files to buffers and arrays for use in rendering, playing music, etc.
		class AssetManager
		{
		public:
			/// <summary>
			/// Loads a texture from a file. (Level data should contain all the textures needed for a level, and what their IDs are)
			/// Subfolder is the directory within the Assets folder to load.
			/// </summary>
			/// 
			static void LoadTextures(const char* subfolder, TEXTURE_LOAD textureLoad = ALL_TEXTURES, bool reloadTextures = false);

			/// <summary>
			/// Loads all the music from a subfolder.
			/// </summary>
			/// <param name="subfolder">The directory within the assets folder to load.</param>
			/// <param name="reloadMusic">If true, all music loaded will be removed before the new music files are loaded.</param>
			static void LoadMusic(const char* subfolder, bool reloadMusic = false);
			
			/// <summary>
			/// Gets the level data file and outputs it to the data array.
			/// </summary>
			/// <param name="subfolder">The directory within the assets folder to load.</param>
			/// <param name="data">Output file.</param>
			static void GetLevelData(const char* subfolder, std::string data[Objects::Levels::LevelDataSize]);

			/// <summary>
			/// Returns the chunk data for a level.
			/// </summary>
			/// <param name="subfolder">The directory within the assets folder to load.</param>
			static std::vector<int> GetChunkData(const char* subfolder);

			/// <summary>
			/// Loads the object data for a level.
			/// </summary>
			/// <param name="subfolder">The directory within the assets folder to load.</param>
			/// <param name="mappings">The mappings to use for initilizing objects. Each mapping should convert a string array to some game object.
			/// The mapping to use is specified by putting the index of the mapping in the mappings array as the first item of each line in the object file.</param>
			/// <param name="reloadObjects">If true, all objects currently loaded will be deleted before loading the new objects. (Should not be called during rendering.)</param>
			static void LoadObjectData(const char* subfolder, std::function<void(std::vector<std::string>)> mappings[], bool reloadObjects = false);


		};
	}
}