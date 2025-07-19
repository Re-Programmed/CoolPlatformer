#include "DialogueSequence.h"

#include "DialogueManager.h"

void GAME_NAME::Cutscenes::DialogueSequence::DialogueEvent::AddOption(const std::string& option)
{
	DialogueSequence ds = DialogueManager::INSTANCE->GetDialogueSequence(option);
	if (!ds.IsEmpty())
	{
		Options.emplace_back(std::make_shared<DialogueSequence>(ds));
	}
#if _DEBUG
	else {
		DEBUG::DebugLog::LogError("Tried to find an dialogue route that goes to \"" + option + "\" but none exist. (DialogueSequence.h:61)");
	}
#endif
}
