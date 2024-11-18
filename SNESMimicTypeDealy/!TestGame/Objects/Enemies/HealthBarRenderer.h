#pragma once

#include "../../../Objects/GameObject.h"

namespace GAME_NAME::Objects::Enemies
{
	class HealthBarRenderer
	{
	public:

		struct HealthBar
		{
			GameObject* BarObject;
			GameObject* BarBackdrop;
			float Value, MaxValue;
		};

		static void CreateHealthBar(GameObject* targetObject, float maxValue, float value = -1);

		static void RemoveHealthBar(GameObject* const targetObject);
		
		static void UpdateHealthBar(GameObject* targetObject, float value);

	private:
		static std::unordered_map<GameObject*, HealthBar> m_createdHealthBars;
	};
}