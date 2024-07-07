#include "LightingSource.h"

#include "SimpleLightingManager.h"

namespace GAME_NAME::Rendering::Lighting
{
	LightingSource::LightingSource(Vec2 position, float power, float falloff, LIGHT_SOURCE_TYPE type, bool defaultOn, bool onDynamic)
		: m_position(position), m_power(power), m_type(type), m_falloffLimit(falloff)
	{
		if(defaultOn)
		{
			On(onDynamic);
		}
	}

	void LightingSource::On(bool dynamic)
	{
		SimpleLightingManager::RegisterSource(this, dynamic);
	}

	void LightingSource::Off(bool dynamic)
	{
		SimpleLightingManager::RemoveSource(this, dynamic);
	}
}