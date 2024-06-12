#pragma once
#include <memory>

namespace GAME_NAME
{
	namespace Objects
	{
		namespace Environment
		{
			class CloudGenerator
			{
			public:
				static void GenerateClouds();

				static inline void SetData(uint8_t skyBegin, uint8_t cloudCount)
				{
					m_skyBeginY = skyBegin;
					m_cloudCount = cloudCount;
				}
			private:
				static uint8_t m_skyBeginY; 
				static uint8_t m_cloudCount;
			};
		}
	}
}