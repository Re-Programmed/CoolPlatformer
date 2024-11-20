#include "../../../../Objects/GameObject.h"

namespace GAME_NAME::Objects::Environment::Buildings
{
	class FrontDoor
		: public GameObject
	{
	public:
		FrontDoor(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, std::string room);
		
		void Update(GLFWwindow* window) override;

	private:
		//The room file to be loaded when the door is entered.
		std::string m_room;

		/// <summary>
		/// Populated with the room contents when the door is opened.
		/// </summary>
		std::vector<GameObject*> m_roomContents;

		/// <summary>
		/// Saves some data after the player enters a room.
		/// </summary>
		struct {
			Vec2 PlayerPosition;
			Vec2 DoorPosition;
			std::string DoorCode;
		} m_enteredState;
	};

}