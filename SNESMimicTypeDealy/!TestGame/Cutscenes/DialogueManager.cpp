#include "DialogueManager.h"

#include "../../Input/InputManager.h"


#include "../Camera/GameCamera.h"

#include <thread>

#define DialogueManager_RenderDialogue(text) Text::TextRenderer::RenderWordCaseSensitive(text, { DIALOGUE_TEXT_BOX_SPACING_X + 12, DIALOGUE_TEXT_BOX_SPACING_Y + 16 }, 9, -3, 1, DEFAULT_FONT_RENDER_A_SPRITE_ID, DEFAULT_FONT_RENDER_LOWERCASE_A_SPRITE_ID, std::chrono::milliseconds(62))

namespace GAME_NAME::Cutscenes
{
	DialogueManager* DialogueManager::INSTANCE = nullptr;
	bool DialogueManager::m_jigglingText = false;

	void DialogueManager::createDialogueBox(int textBoxTexture)
	{
		if (!m_playingDialogueSequence) { return; }
		//A textbox already exists, failure.
		if (std::get<0>(m_guiDisplay) != nullptr) { return; }
		Sprite* sp = Renderer::GetSprite(textBoxTexture);
		StaticGUIElement* textBox = new StaticGUIElement({ DIALOGUE_TEXT_BOX_SPACING_X, DIALOGUE_TEXT_BOX_SPACING_Y }, { TargetResolutionX - (2 * DIALOGUE_TEXT_BOX_SPACING_X), 25}, sp->GetSpriteId());
		delete sp;
		Renderer::LoadGUIElement(textBox);

		DialogueSequence::DialogueEvent next = m_currentDialogueSequence.Next();
		Text::TextRenderer::ExpectedRenderedWord erw = DialogueManager_RenderDialogue(next.Text);
		m_guiDisplay = std::tuple<StaticGUIElement*, Text::TextRenderer::ExpectedRenderedWord>(textBox, erw);

			//--- Handle camera --//

		if (next.FocusObject != nullptr)
		{
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->LockCamera(next.FocusObject);
		}

		if (next.Zoom > 0)
		{
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->SetTargetZoom(next.Zoom);
		}

	}

	bool advancingDialogue = false;

	void DialogueManager::Update(GLFWwindow* window)
	{
		if (m_playingDialogueSequence)
		{
			if (InputManager::GetMouseButton(0))
			{
				if (!advancingDialogue)
				{
					if (!advanceDialogue() && !m_jigglingText)
					{
						m_jigglingText = true;
						std::thread t = std::thread([](Text::TextRenderer::ExpectedRenderedWord gui) {

							for (int i = 0; i < 4; i++)
							{
								for (int j = 0; j < gui.size(); j++)
								{
									Text::TextRenderer::ExpectedLetter* letter = gui[j];

									letter->letterLock.lock();
									letter->letter->SetPosition(letter->letter->GetPosition() + Vec2{ 0, ((i + j) % 2 == 0) ? 1.3f : -1.3f});
									letter->letterLock.unlock();
								}

								std::this_thread::sleep_for(std::chrono::milliseconds(3));
							}

							m_jigglingText = false;

						}, std::get<1>(m_guiDisplay));

						t.detach();
					}

					advancingDialogue = true;
				}
			}
			else {
				advancingDialogue = false;
			}
		}
	}

	bool DialogueManager::advanceDialogue()
	{
		//Advancing dialogue with a menu open breaks the menu, so don'ten't.
		if (TestGame::GetGamePaused())
		{
			return false;
		}

		if (!m_playingDialogueSequence) { return false; }
		//A textbox does not exist, create it.
		if (std::get<0>(m_guiDisplay) == nullptr) { createDialogueBox(); }

		for (Text::TextRenderer::ExpectedLetter* letter : std::get<1>(m_guiDisplay))
		{
			//The mutex is locked, therefore the text is getting modified so we cannot currently advance dialogue.
			if (letter->letterLock.try_lock())
			{
				letter->letterLock.unlock();
			}
			else
			{
				return false;
			}
		}


		for (Text::TextRenderer::ExpectedLetter* letter : std::get<1>(m_guiDisplay))
		{
			Renderer::UnloadGUIElement(letter->letter);

			delete letter->letter;
			delete letter;
		}

		DialogueSequence::DialogueEvent next = m_currentDialogueSequence.Next();

		if (next.Text.empty())
		{
			//We are at the end of the dialogue.
			stopDialogue();

			return true;
		}

		Text::TextRenderer::ExpectedRenderedWord erw = DialogueManager_RenderDialogue(next.Text);
		m_guiDisplay = std::tuple<StaticGUIElement*, Text::TextRenderer::ExpectedRenderedWord>(std::get<0>(m_guiDisplay), erw);

			//--- Handle camera --//

		if (next.FocusObject != nullptr)
		{
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->LockCamera(next.FocusObject);
		}

		if (next.Zoom > 0)
		{
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->SetTargetZoom(next.Zoom);
		}

		return true;
	}

	void DialogueManager::destroyDialogueBox()
	{
		if (std::get<0>(m_guiDisplay) == nullptr) { return; }

		Renderer::UnloadGUIElement(std::get<0>(m_guiDisplay));
		delete std::get<0>(m_guiDisplay);

		m_guiDisplay = std::tuple<StaticGUIElement*, Text::TextRenderer::ExpectedRenderedWord>(nullptr, NULL);
	}
}
