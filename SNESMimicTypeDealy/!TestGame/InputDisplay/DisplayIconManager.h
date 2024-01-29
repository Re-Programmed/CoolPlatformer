#pragma once
#include "../../Objects/GameObject.h"
#include "../../Rendering/Renderers/Renderer.h"

#define DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT 1

namespace GAME_NAME::Input
{
	class DisplayIconManager
	{
	public:
		enum KEY_DISPLAY
		{
			INPUT_DISPLAY_KEY_E	//Progress 0-9
		};

		/// <summary>
		/// Render a key prompt with progress.
		/// </summary>
		/// <param name="keyDisplay"></param>
		/// <param name="anchor"></param>
		static void ShowKeyInputDisplay(KEY_DISPLAY keyDisplay, Vec2 anchor, char progress = 0);
		
		/// <summary>
		/// Called each frame to destroy any icons that are no longer in use.
		/// </summary>
		static void AttemptHideIcons();

		/// <summary>
		/// Called on game start.
		/// </summary>
		static void CreateKeyDisplayObjects();
	private:
		static Objects::GameObject* m_keyDisplayObjects[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];	//The game objects that are copied to represent each key icon.
		static int m_keyDisplayBaseTextures[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];				//The texture ids for each key icon with 0 progress.

		static Objects::GameObject* m_activeDisplays[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];	//The current active displays, nullptr if not active.
		static bool m_wasShown[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];							//If the key was displayed on this frame.
	};
}