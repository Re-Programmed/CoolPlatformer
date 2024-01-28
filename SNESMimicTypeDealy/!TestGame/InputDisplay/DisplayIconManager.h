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
			INPUT_DISPLAY_KEY_E
		};

		struct ScheduledIcon
		{
			KEY_DISPLAY KeyDisplay; Vec2 Anchor; char Progress;
			ScheduledIcon(KEY_DISPLAY keyDisplay, Vec2 anchor, char progress = 0)
				: KeyDisplay(keyDisplay), Anchor(anchor), Progress(progress)
			{

			}
		};

		static void RenderAllIcons();

		/// <summary>
		/// Render a key prompt with progress.
		/// </summary>
		/// <param name="keyDisplay"></param>
		/// <param name="anchor"></param>
		static void ShowKeyInputDisplay(KEY_DISPLAY keyDisplay, Vec2 anchor, char progress = 0);
		
		/// <summary>
		/// Called on game start.
		/// </summary>
		static void CreateKeyDisplayObjects();
	private:
		static Objects::GameObject* m_keyDisplayObjects[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
		static int m_keyDisplayBaseTextures[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];

		static std::vector<ScheduledIcon> m_scheduledIcons;
	};
}