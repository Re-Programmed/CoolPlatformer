#pragma once
#include <string>

namespace GAME_NAME::Objects::Player
{
	/// <summary>
	/// The type of skill, used to check what abilities the player should have while using a skill.
	/// </summary>
	enum SKILL_TYPE
	{
		NO_SKILL,
		FLIGHT
	};

	struct SkillData
	{
		const SKILL_TYPE Type;
		const std::string Name;
	};

	const SkillData Skills[2]
	{
		{ NO_SKILL, "No Skill" },
		{ FLIGHT, "Wings" }
	};

	

}