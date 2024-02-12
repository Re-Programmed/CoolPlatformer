#pragma once

/*
	This file contains settings that you will need to change based on what features you use in the engine and where you put certain files.
*/

#pragma region Renderer	
	
	#define GLOBAL_SPRITE_BASE -64								//Represents the negative number of sprites in the global_sprites directory.

#pragma endregion

#pragma region TextRenderer	

	#define TEXT_RENDERER_ZERO_DIGIT_SPRITE_ID SpriteBase(54)	//The texture used for the digit 0. All subsequent digits should be after it in ascending order.
	#define TEXT_RENDERER_DIGIT_SIZE_X 20.f						//The X scale of all digits rendered by the text renderer.
	#define TEXT_RENDERER_DIGIT_SIZE_Y 24.f						//The Y scale of all digits rendered by the text renderer.

#pragma endregion
