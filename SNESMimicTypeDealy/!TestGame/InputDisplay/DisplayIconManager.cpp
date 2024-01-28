#include "DisplayIconManager.h"

#include "../../!TestGame/TestGame.h"

namespace GAME_NAME::Input
{
	Objects::GameObject* DisplayIconManager::m_keyDisplayObjects[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
	int DisplayIconManager::m_keyDisplayBaseTextures[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
	std::vector<DisplayIconManager::ScheduledIcon> DisplayIconManager::m_scheduledIcons;

	void DisplayIconManager::RenderAllIcons()
	{
		for (ScheduledIcon icon : m_scheduledIcons)
		{
			std::cout << std::to_string(icon.Progress) << std::endl;
			m_keyDisplayObjects[icon.KeyDisplay]->SetSprite(Renderer::GetSprite(m_keyDisplayBaseTextures[icon.KeyDisplay] + icon.Progress));
			m_keyDisplayObjects[icon.KeyDisplay]->SetPosition(icon.Anchor);
			m_keyDisplayObjects[icon.KeyDisplay]->Render(TestGame::INSTANCE->GetCamera()->GetPosition());
		}

		m_scheduledIcons.clear();
	}

	void DisplayIconManager::ShowKeyInputDisplay(KEY_DISPLAY keyDisplay, Vec2 anchor, char progress)
	{
		m_scheduledIcons.push_back(ScheduledIcon(keyDisplay, anchor, progress));
	}

	void DisplayIconManager::CreateKeyDisplayObjects()
	{
		using namespace Objects;

		GameObject* eIcon = new GameObject(Vec2(0, 0), Vec2(12), Renderer::GetSprite(SpriteBase(45)), 0.0f);

		m_keyDisplayObjects[0] = eIcon;
		m_keyDisplayBaseTextures[0] = SpriteBase(45);
	}
}

