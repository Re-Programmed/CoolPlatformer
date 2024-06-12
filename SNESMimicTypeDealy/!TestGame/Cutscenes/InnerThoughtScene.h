#pragma once
#include <string>
#include "./Cutscene.h"

namespace GAME_NAME::Cutscenes
{
	class InnerThoughtScene
		: public Cutscene
	{
	public:
		InnerThoughtScene(Vec2 position, float triggerDistance, std::string text);

		bool Trigger() override;
	private:
		const std::string m_text;
	};
}