#pragma once

#include "DialogueSequence.h"
#include "../../Objects/GUI/StaticGUIElement.h"
#include "../../Objects/GUI/Text/TextRenderer.h"
#include "../TestGame.h"

#include "../../Utils/ConstUpdateable.h"

using namespace GAME_NAME::Objects::GUI;

#define DIALOGUE_TEXT_BOX_SPACING_X 40
#define DIALOGUE_TEXT_BOX_SPACING_Y 5
#define DIALOGUE_TEXT_BOX_TEXTURE SpriteBase(-1)

namespace GAME_NAME::Cutscenes
{
	class DialogueManager
		: public Utils::ConstUpdateable
	{
	public:
		static DialogueManager* INSTANCE;

		static void Init()
		{
			if (INSTANCE != nullptr) { return; }
			DialogueManager* d = new DialogueManager();
			INSTANCE = d;
		}

		inline bool PlayDialogueSequence(DialogueSequence sequence)
		{
			if (m_playingDialogueSequence)
			{
				return false;
			}

			m_currentDialogueSequence = sequence;
			m_playingDialogueSequence = true;

			createDialogueBox();
			return true;
		}

		DialogueManager()
			: m_guiDisplay(nullptr, NULL), m_currentDialogueSequence(0, DialogueSequence::DialogueEvent("", nullptr))
		{

		}

		~DialogueManager()
		{
			if (std::get<0>(m_guiDisplay))
			{
				Renderer::UnloadGUIElement(std::get<0>(m_guiDisplay));
				delete std::get<0>(m_guiDisplay);
			}
		}

		void Update(GLFWwindow* window) override;

	private:
		bool m_playingDialogueSequence = false;
		DialogueSequence m_currentDialogueSequence;

		static bool m_jigglingText;

		std::tuple<StaticGUIElement*, Text::TextRenderer::ExpectedRenderedWord> m_guiDisplay;

		bool advanceDialogue();

		inline void stopDialogue()
		{
			if (!m_playingDialogueSequence)
			{
				return;
			}

			//Ensure the camera goes back to normal after the cutscene.
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->UnlockCamera();
			static_cast<GAME_NAME::Camera::GameCamera*>(TestGame::INSTANCE->GetCamera())->SetTargetZoom(1.f);

			destroyDialogueBox();

			m_playingDialogueSequence = false;
			m_currentDialogueSequence = DialogueSequence(0, DialogueSequence::DialogueEvent("", nullptr));
		}

		void createDialogueBox(int textBoxTexture = DIALOGUE_TEXT_BOX_TEXTURE);
		void destroyDialogueBox();
	};
}