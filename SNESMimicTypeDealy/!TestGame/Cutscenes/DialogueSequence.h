#pragma once

#include "../../Objects/GameObject.h"
#include <queue>
#include <cstdarg>

using namespace GAME_NAME::Objects;

namespace GAME_NAME::Cutscenes
{
	class DialogueSequence
	{
	public:
		struct DialogueEvent
		{
			std::string Text;
			GameObject* FocusObject;

			float Zoom;
			std::vector<std::shared_ptr<DialogueSequence>> Options;

			DialogueEvent(std::string text, GameObject* focusObject = nullptr, float zoom = 1.f)
				: Text(text), FocusObject(focusObject), Zoom(zoom)
			{

			}

			DialogueEvent(std::string text, GameObject* focusObject, float zoom, int numOptions, std::shared_ptr<DialogueSequence> options...)
				: Text(text), FocusObject(focusObject), Zoom(zoom)
			{
				va_list args;
				va_start(args, numOptions);

				for (unsigned int i = 0; i < numOptions; i++)
				{
					Options.push_back(va_arg(args, std::shared_ptr<DialogueSequence>));
				}

				va_end(args);
			}
		};

		/// <summary>
		/// Creates a dialogue sequence with the given events.
		/// </summary>
		/// <param name="numEvents">How many dialogue events are listed.</param>
		/// <param name="...">A list of dialogue events.</param>
		DialogueSequence(unsigned int numEvents, DialogueEvent events...)
		{
			va_list args;
			va_start(args, numEvents);
			
			for (unsigned int i = 0; i < numEvents; i++)
			{
				m_dialogueEvents.push(va_arg(args, DialogueEvent));
			}

			va_end(args);
		}


		/// <summary>
		/// Returns the next dialogue event and pops it from the dialogue queue.
		/// </summary>
		/// <returns></returns>
		inline DialogueEvent Next()
		{
			if (m_dialogueEvents.empty()) { return DialogueEvent(""); };

			DialogueEvent de = m_dialogueEvents.front();
			m_dialogueEvents.pop();
			return de;
		}

	private:
		/// <summary>
		/// A queue of all upcoming dialogue events.
		/// </summary>
		std::queue<DialogueEvent> m_dialogueEvents;
	};
}