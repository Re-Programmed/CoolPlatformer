#pragma once
#include "../../Utils/Math/Vec2.h"

namespace GAME_NAME::Rendering::Lighting
{

using namespace MathUtils;

	enum LIGHT_SOURCE_TYPE
	{
		POINT_LIGHT,
		SPOT_LIGHT
		/* SPOT_LIGHT
			Positive Power / Positive Falloff: Right
			Negative Power / Positive Falloff: Left
			Positive Power / Negative Falloff: Down
			Negative Power / Negative Falloff: Up
		*/
	};

	class LightingSource
	{
	public:
		/// <summary>
		/// Create a light source with position, power, and type.
		/// </summary>
		/// <param name="position">[Vec2] - Where the light origin is.</param>
		/// <param name="power">[float] - How strong the light is (radius).</param>
		/// <param name="type">[LIGHT_SOURCE_TYPE] - What kind of light this is.</param>
		/// <param name="defaultOn">[bool] - Should the light start on?</param>
		LightingSource(Vec2 position, float power, float falloff, LIGHT_SOURCE_TYPE type, bool defaultOn = true, bool onDynamic = false);

		/// <summary>
		/// Turns this light source on.
		/// </summary>
		void On(bool dynamic);
		/// <summary>
		/// Disables this light source.
		/// </summary>
		void Off(bool dynamic);

		/// <summary>
		/// Update the position of the light.
		/// (SHOULD ONLY REALLY BE CALLED ON DYNAMIC LIGHTS)
		/// IF THIS IS CALLED ON A NON-DYNAMIC LIGHT, ENSURE THAT IT NEVER LEAVES THE BOUNDS OF ITS LIGHT GROUP.
		/// </summary>
		/// <param name="position">[Vec2] - Light Position.</param>
		inline void SetPosition(Vec2 position)
		{
			m_position = position;
		}

		inline const Vec2 GetPosition()
		{
			return m_position;
		}

		inline const LIGHT_SOURCE_TYPE GetType()
		{
			return m_type;
		}

		inline const float GetPower()
		{
			return m_power;
		}

		inline const float GetFalloff()
		{
			return m_falloffLimit;
		}

	private:
		const LIGHT_SOURCE_TYPE m_type;

		Vec2 m_position;
		float m_power;
		/// <summary>
		/// The radius of the circle within the light where it is always at full brightness.
		/// </summary>
		float m_falloffLimit;
	};
}