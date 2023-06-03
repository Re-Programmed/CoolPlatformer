#pragma once
#include "../glad/include/glad/glad.h"
#include <iostream>
#include <filesystem>

constexpr const char* AssetPath = "./Assets";
constexpr const char* SpriteSubfolder = "/sprite";
constexpr const char* BGSubfolder = "/bg";

constexpr const char* ChunkFileName = "/chunk.pk";

constexpr const char* MusicFilePath = "/music";

///Max number of assets to store at one time.
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
		class AssetManager
		{
		public:
			/// <summary>
			/// Loads a texture from a file. (Level data should contain all the textures needed for a level, and what their IDs are)
			/// Subfolder is the directory within the Assets folder to load.
			/// </summary>
			static void LoadTextures(const char* subfolder, TEXTURE_LOAD textureLoad = ALL_TEXTURES, bool reloadTextures = false);
			static void LoadMusic(const char* subfolder, bool reloadMusic = false);

			static std::vector<int> GetChunkData(const char* subfolder);
		};
	}
}