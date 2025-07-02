#pragma once

namespace GAME_NAME::Objects::Environment::Effects
{
	class GlitchableObject
	{
	public:
		virtual void SetGlitched(bool glitched)
		{
			m_isGlitched = glitched;
		}

		inline const bool& GetGlitched()
		{
			return m_isGlitched;
		}

	protected:
		bool m_isGlitched = false;
	};
}