#include "SettingsManager.h"
#include "../Objects/GUI/Text/TextRenderer.h"
#include "../Input/InputManager.h"

#include "../Objects/GUI/GUIButton.h"
#include "../Objects/GUI/GUIManager.h"

#include "./TestGame.h"

#include <algorithm>

//The amount that a GLFW_KEY should be offset to become a displayable char.
#define LETTER_DISPLAY_OFFSET ('a' - GLFW_KEY_A)

namespace GAME_NAME
{
	std::vector<StaticGUIElement*> SettingsManager::m_currentPageElements;

	std::vector<StaticGUIElement*> SettingsManager::m_controlsPageNumbers;

	std::vector<StaticGUIElement*> SettingsManager::m_recordingText;

	bool SettingsManager::m_settingsMenuOpen = false;

	bool SettingsManager::m_recordingKey = false;
	int SettingsManager::m_currentRecordingIndex = -1;
	

	void SettingsManager::CreateSettingsMenu()
	{
		m_settingsMenuOpen = true;

		Renderer::UpdateObjects = false;

		GUI::Menus::GUIMenu::LoadMenu("/settings", new std::function(mainMenu_guiCallback));
	}


	double SettingsManager_currentControlsMenuScroll = 0.0; //Used to determine where the top and bottom of the scrolling page should be.
	StaticGUIElement* SettingsManager_applyButton = nullptr;

	void SettingsManager::OpenControlsMenu()
	{
		glfwSetScrollCallback(TestGame::FirstWindow, controlsMenu_scrollCallback);

		m_settingsMenuOpen = true;
		
		Renderer::UpdateObjects = false;

		SettingsManager_currentControlsMenuScroll = 0;

		//GUI::Menus::GUIMenu::LoadMenu("/settings_controls", new std::function(controlsMenu_guiCallback));

		GUI::StaticGUIElement* backing = new GUI::StaticGUIElement({ 0.f, -800.f }, { 400.f, 1000.f }, Renderer::GetSprite(SpriteBase(-1))->GetSpriteId());
		Renderer::LoadGUIElement(backing, 1);

		m_currentPageElements.push_back(backing);

		Text::TextRenderer::RenderedWord controlsName = Text::TextRenderer::RenderWord("controls", Vec2(118, 161), 12.f, 0.f, 2);
		m_currentPageElements.insert(m_currentPageElements.end(), controlsName.begin(), controlsName.end());

using namespace GUI::Text;

		GUI::GUIButton* applyButton = new GUI::GUIButton(Vec2(78.6f, 118.f), Vec2(72.f, 16.f), Renderer::GetSprite(72)->GetSpriteId(), new std::function(controlsMenu_guiCallback), Vec4{ 0.f, 0.75f, 0.f, 1.f });
		Renderer::LoadGUIElement(applyButton, 2);
		SettingsManager_applyButton = applyButton;
		m_currentPageElements.push_back(applyButton);
		SettingsManager_currentControlsMenuScroll = SettingsManager_applyButton->GetPosition().Y;
		GUI::GUIManager::RegisterButton(applyButton);

		GUI::GUIButton* closeButton = new GUI::GUIButton(Vec2(162.f, 118.f), Vec2(72.f, 16.f), Renderer::GetSprite(72)->GetSpriteId(), new std::function(controlsMenu_guiCallback), Vec4{ 0.75f, 0.f, 0.f, 1.f });
		Renderer::LoadGUIElement(closeButton, 2);
		m_currentPageElements.push_back(closeButton);
		GUI::GUIManager::RegisterButton(closeButton);

		auto applyWords = TextRenderer::RenderWord("Apply", Vec2(96.6f, 120.f), 12.f, 0.f, 2);
		m_currentPageElements.insert(m_currentPageElements.end(), applyWords.begin(), applyWords.end());

		auto closeWords = TextRenderer::RenderWord("Close", Vec2(180.f, 120.f), 12.f, 0.f, 2);
		m_currentPageElements.insert(m_currentPageElements.end(), closeWords.begin(), closeWords.end());

		for (int i = 0; i < KEY_ARRAY_SIZE; i++)
		{
			std::string name = KeybindNames[i];
			std::replace(name.begin(), name.end(), '_', ' ');
			TextRenderer::RenderedWord keyName = TextRenderer::RenderWord(name, Vec2(24, 102.f - (i * 16.f)), 8.f, 0.f, 2);
			m_currentPageElements.insert(m_currentPageElements.begin(), keyName.begin(), keyName.end());

			Vec2 keyDisplayPosition = Vec2(250, 102.f - (i * 16.f));

			GUI::GUIButton* keyInput = new GUI::GUIButton(keyDisplayPosition, Vec2(12.f, 12.f), Renderer::GetSprite(72)->GetSpriteId(), new std::function(controlsMenu_guiCallback), Vec4{ 0.6f, 0.2f, 0.4f, 1.f }, Vec4{ 1.f, 1.f, 0.f, 1.f });
			GUI::GUIManager::RegisterButton(keyInput);
			Renderer::LoadGUIElement(keyInput);
			m_currentPageElements.push_back(keyInput);

			keyDisplayPosition.X += 12.f;

			if (InputManager::GetKeybindValue(i) <= GLFW_KEY_9 && InputManager::GetKeybindValue(i) >= GLFW_KEY_0)
			{
				Vec2 pos = (keyDisplayPosition + Vec2(-1.4f, 1.f));
				StaticGUIElement* digit = TextRenderer::RenderDigit(InputManager::GetKeybindValue(i) - GLFW_KEY_0, pos, 12.f / 32.f);
				m_currentPageElements.push_back(digit);
				m_controlsPageNumbers.push_back(digit);
			}
			else {
				TextRenderer::Letter keyLetterDisplay = TextRenderer::RenderLetter(InputManager::GetKeybindValue(i) + LETTER_DISPLAY_OFFSET, keyDisplayPosition, 12.f, 2);
				m_controlsPageNumbers.push_back(keyLetterDisplay);
				m_currentPageElements.push_back(keyLetterDisplay);
			}
		}
	}

	void SettingsManager::mainMenu_guiCallback(int id)
	{
		std::cout << "ID OF BUTTON: " << id << std::endl; //TESTING BUTTONS.

		//Controls button.
		if (id == 0)
		{
			CloseMenu();
			OpenControlsMenu();
			return;
		}

		//Back button.
		if (id == 1)
		{
			CloseMenu();
			return;
		}
	}

	void SettingsManager::controlsMenu_guiCallback(int id)
	{
		if (m_recordingKey) { return; }

		if (id == 0)
		{
			//Apply button.
			InputManager::SaveAllKeybinds();
		}

		if (id <= 1)
		{
			m_controlsPageNumbers.clear();

			for (GUI::StaticGUIElement* el : m_currentPageElements)
			{
				if (el == nullptr) { continue; }

				Renderer::UnloadGUIElement(el, 1);
				Renderer::UnloadGUIElement(el, 2);

				/*
					BUG WITH THE FACT TAHT UPDATING A KEYBIND CAUSES A NULL OBJECT TO EXIST IN THE m_currentPageElements ARRAY.
				*/

				try {
					if (GUI::GUIButton* button = dynamic_cast<GUI::GUIButton*>(el))
					{
						GUIManager::UnregisterButton(button);
					}
				}
				catch (...)
				{

				}

				delete el;
			}

			m_currentPageElements.clear();
			
			CloseMenu(true);

			return;
		}

		m_currentRecordingIndex = id - 2;

		std::cout << "ID OF BUTTON: " << id << std::endl; //TESTING BUTTONS.

		m_recordingKey = true;

		m_recordingText = Text::TextRenderer::RenderWord("Recording", Vec2(100.f, 40.f), 16.f, 0.f, 2);

		//Record keys to detect what the player is binding.
		std::thread recordThread([]() {

			while (true)
			{
				if (m_currentRecordingIndex < 0) { break; }
				if (!m_recordingKey) { break; }

				for (int i = 0; i < m_recordingText.size(); i++)
				{
					m_recordingText[i]->SetScale({ (2.f + (float)std::sin(glfwGetTime())) * -16.f/3.f, (2.f + (float)std::sin(glfwGetTime())) * 16.f/3.f });
				}

				//SOMEHOW DISPLAY WHAT KEY IS GETTING RECORDED TO.
				//m_controlsPageNumbers[m_currentRecordingIndex]->SetScale({ -20.f/4.f * (2.f + (float)std::sin(glfwGetTime() * 2.0)), 12.f });

				/*
					FIX TO WORK WITH ALL KEYS, NOT JUST LETTERS.
				*/

				for (int i = 48; i <= 90; i++)
				{
					if (glfwGetKey(TestGame::FirstWindow, i) == GLFW_PRESS)
					{
						//Update keybind graphic.
						m_recordingKey = false;
						StaticGUIElement* const lastElement = m_controlsPageNumbers[m_currentRecordingIndex];
						Renderer::UnloadGUIElement(m_controlsPageNumbers[m_currentRecordingIndex], 2);
						m_controlsPageNumbers[m_currentRecordingIndex] = Text::TextRenderer::RenderLetter(i + LETTER_DISPLAY_OFFSET, lastElement->GetPosition(), lastElement->GetScale().Y, 2);
						m_currentPageElements.push_back(m_controlsPageNumbers[m_currentRecordingIndex]);
						delete lastElement;

						for (int i = 0; i < m_recordingText.size(); i++)
						{
							Renderer::UnloadGUIElement(m_recordingText[i], 2);
							delete m_recordingText[i];
						}

						m_recordingText.clear();

						//Update keybind data.
						InputManager::UpdateKeybind((keyRef)m_currentRecordingIndex, i);
						break;
					}
				}
			}
		});

		recordThread.detach();
	}


	void SettingsManager::controlsMenu_scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		//Invert & increase scroll sensitivity.
		yOffset *= -4.0;


		//Prevent scrolling up more than the apply button.
		if (SettingsManager_applyButton->GetPosition().Y < SettingsManager_currentControlsMenuScroll && yOffset < 0)
		{
			return;
		}
		
		for (GUI::StaticGUIElement* element : m_currentPageElements)
		{
			if (element == nullptr) { continue; }
			element->SetPosition({ element->GetPosition().X, element->GetPosition().Y + (float)yOffset });
		}
	}
}
