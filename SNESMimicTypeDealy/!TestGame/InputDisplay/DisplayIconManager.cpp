#include "DisplayIconManager.h"

#include "../../!TestGame/TestGame.h"

namespace GAME_NAME::Input
{
	Objects::GameObject* DisplayIconManager::m_keyDisplayObjects[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
	int DisplayIconManager::m_keyDisplayBaseTextures[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
	Objects::GameObject* DisplayIconManager::m_activeDisplays[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];
	bool DisplayIconManager::m_wasShown[DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT];

	void DisplayIconManager::ShowKeyInputDisplay(KEY_DISPLAY keyDisplay, Vec2 anchor, char progress)
	{
		if (m_activeDisplays[keyDisplay] == nullptr)
		{
			std::cout << "SHOWING INPUT DISPLAY\n";
			m_activeDisplays[keyDisplay] = new GameObject(*m_keyDisplayObjects[0]);
			Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_activeDisplays[keyDisplay], true, 2, true));
		}

		m_activeDisplays[keyDisplay]->SetSprite(Renderer::GetSprite(m_keyDisplayBaseTextures[keyDisplay] + progress));
		m_activeDisplays[keyDisplay]->SetPosition(anchor);

		m_wasShown[keyDisplay] = true;
	}

	void DisplayIconManager::AttemptHideIcons()
	{
		for (int i = 0; i < DISPLAY_ICON_MANGER_KEY_DISPLAY_COUNT; i++)
		{
			if (m_activeDisplays[i] != nullptr && !m_wasShown[i])
			{
				Renderer::DestroyActiveObject(m_activeDisplays[i]);
				m_activeDisplays[i] = nullptr;
			}

			m_wasShown[i] = false;
		}
	}

	void DisplayIconManager::CreateKeyDisplayObjects()
	{
		using namespace Objects;

		GameObject* eIcon = new GameObject(Vec2(0, 0), Vec2(-6, 6), Renderer::GetSprite(SpriteBase(44)), 0.0f);

		m_keyDisplayObjects[0] = eIcon;
		m_keyDisplayBaseTextures[0] = SpriteBase(44);
		m_activeDisplays[0] = nullptr;
	}
}

