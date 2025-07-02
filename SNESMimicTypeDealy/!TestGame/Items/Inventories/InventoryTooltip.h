#pragma once
#include "../../../Objects/GUI/StaticGUIElement.h"
#include "./InventoryContainer.h"

namespace GAME_NAME::Items::Inventories 
{
	using namespace Objects::GUI;

	class InventoryTooltip
	{
	public:
		static void UpdateTooltip(uint8_t index, Inventory::ReturnItem item, bool clearTooltip = false, bool invertTooltipPosition = false);

		static void RemoveTooltip();

		static void CreateTooltip();

	private:
		static bool m_hidingTooltip;

		static StaticGUIElement* m_tooltip;
		/// <summary>
		/// The objects that make up the parts of the tooltip.
		/// </summary>
		static std::vector<StaticGUIElement*> m_tooltipComponents;
		static std::vector<float> m_tooltipComponentsApproachedScales;

		/// <summary>
		/// How tall the curent tooltip is. This will change based on how much text must display.
		/// </summary>
		static float m_tooltipHeight;

	};
}