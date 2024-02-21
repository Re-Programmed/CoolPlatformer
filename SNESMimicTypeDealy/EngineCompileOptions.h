#pragma once

/*
	This file contains settings that you will need to change based on what features you use in the engine and where you put certain files.
*/

#pragma region Renderer	
	
	/*
	---RENDER ORDER---

	   [BACKGROUND] {Static.}
	   [RENDER LAYER 0] {Bound to the chunk spawned in.}
	   [RENDER LAYER 1]	|
	   [RENDER LAYER 2]	|
	   [RENDER LAYER 3]	|
	   [ACTIVE RENDER LAYER 0] {Rendered if visible by camera.}
	   [ACTIVE RENDER LAYER 1]		|
	   [ACTIVE RENDER LAYER 2]		|	(PLAYER)
	   [ACTIVE RENDER LAYER 3]		|
	   [PRIORITY OBJECTS (FRONT OBJECTS)] {Bound to the chunk spawned in.}
	   [GUI LAYER 0] {Always rendered.}
	   [GUI LAYER 1]	|
	   [GUI LAYER 2]	|
	*/

	#define GLOBAL_SPRITE_BASE -64								//Represents the negative number of sprites in the global_sprites directory.

#pragma endregion

#pragma region TextRenderer	

	#define TEXT_RENDERER_ZERO_DIGIT_SPRITE_ID SpriteBase(54)	//The texture used for the digit 0. All subsequent digits should be after it in ascending order.
	#define TEXT_RENDERER_DIGIT_SIZE_X 20.f						//The X scale of all digits rendered by the text renderer.
	#define TEXT_RENDERER_DIGIT_SIZE_Y 24.f						//The Y scale of all digits rendered by the text renderer.

#pragma endregion
