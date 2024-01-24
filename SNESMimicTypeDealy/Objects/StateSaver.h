#pragma once

#include <vector>
#include "./GameObjectState.h"
#include <memory>


namespace GAME_NAME::Objects
{
	/// <summary>
	/// Used to save object states.
	/// </summary>
	class StateSaver
	{
	public:
		/// <summary>
		/// Registers a GameObjectState to be saved on the next save.
		/// </summary>
		/// <param name="state"></param>
		static void RegisterToBeSaved(GameObjectState* state);

		/// <summary>
		/// Saves all currently registered GameObjectStates and clears the cache.
		/// </summary>
		static void SaveStates();
	private:
		/// <summary>
		/// A list of all the objects that have been modified and, therefore, should be saved on the next save.
		/// </summary>
		static std::vector<GameObjectState*> m_toBeSaved;

	};
}