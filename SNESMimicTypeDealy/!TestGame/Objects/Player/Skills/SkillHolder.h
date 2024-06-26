#pragma once

#include "./SkillType.h"
#include "../../../../Utils/Math/Vec2.h"
#include "../../../../Objects/GUI/GUIButton.h"
#include "../Backpack/Backpack.h"

namespace GAME_NAME::Objects::Player
{
using namespace MathUtils;
using namespace GUI;

	/// <summary>
	/// Manages effects applied to the player by a skill or equipment.
	/// </summary>
	class SkillHolder
	{
	public:
		SkillHolder(const Vec2& skillDisplayPosition);

		~SkillHolder();

		void SetCurrentSkill(SKILL_TYPE type);

		inline bool CanUseAbility(SKILL_TYPE ability) { return m_currentSkill == ability; }

		/// <summary>
		/// Should be called each frame to update the display.
		/// </summary>
		void Update();

		/// <summary>
		/// Returns the amount of boost given to the provided effect based on the given backpack.
		/// </summary>
		/// <param name="effect"></param>
		/// <param name="backpack"></param>
		/// <returns></returns>
		float GetEquipmentBoostEffect(std::string effect, Backpack* backpack);

		inline void UnlockSkill(SKILL_TYPE skill)
		{
			if (std::find(m_unlockedSkills.begin(), m_unlockedSkills.end(), skill) != m_unlockedSkills.end()) { return; }
			m_unlockedSkills.push_back(skill);
		}

		inline bool GetSkillMenuIsOpen() { return m_skillMenuIsOpen; }
	private:
		SKILL_TYPE m_currentSkill;

		/// <summary>
		/// A list of all skills the player has unlocked.
		/// TODO: SAVE THIS LIST ON GAME SAVE.
		/// </summary>
		std::vector<SKILL_TYPE> m_unlockedSkills;

		StaticGUIElement* m_skillDisplay;

		/// <summary>
		/// True if the skill selector is open.
		/// </summary>
		bool m_skillMenuIsOpen = false;

		/// <summary>
		/// All skill menu options.
		/// </summary>
		std::vector<GUIButton*> m_skillMenuButtons;

		/// <summary>
		/// Creates the skill selection GUI.
		/// </summary>
		void OpenSkillMenu();
		/// <summary>
		/// Removes the skill menu if it is open. (occurs when a skill is selected)
		/// </summary>
		void CloseSkillMenu();

		static SkillHolder* m_currentOpenSkillHolder;
		static void skillMenuButtonClicked(int id);
	};
}