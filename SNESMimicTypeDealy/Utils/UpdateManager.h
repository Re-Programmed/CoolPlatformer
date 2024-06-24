#pragma once
#include "IUpdateable.h"
#include <vector>

namespace GAME_NAME
{
	namespace Utils
	{
		/// <summary>
		/// Call update each frame to update all IUpdateables.
		/// </summary>
		class UpdateManager
		{
		public:
			/// <summary>
			/// Calls update on all updateables.
			/// </summary>
			/// <param name="window"></param>
			static void Update(GLFWwindow* window);

			/// <summary>
			/// Registers an IUpdateable to be called each frame.
			/// </summary>
			/// <param name="updateable">The IUpdateable to be called each frame.</param>
			/// <returns>The index of the IUpdateable in the updateables vector.</returns>
			static UpdateIndex RegisterUpdateable(IUpdateable* updateable);

			/// <summary>
			/// Removes an IUpdateable from getting updated.
			/// </summary>
			/// <param name="index">The index of the IUpdateable to remove.</param>
			static void RemoveUpdateable(const UpdateIndex index);
		private:
			/// <summary>
			/// INFO: 
			/// STATIC UPDATEABLES MUST BE ADDED TO THE m_updateables ARRAY IN UPDATE MANAGER.
			/// </summary>
			static std::vector<IUpdateable*> m_updateables;
		};
	}
}