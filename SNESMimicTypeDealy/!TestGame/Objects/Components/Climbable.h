#include "../../../Objects/GameObject.h"
#include "../../../Components/IComponent.h"

namespace GAME_NAME::Objects::Util
{
	using namespace GAME_NAME::Components;

	class Climbable
		: public IComponent
	{
	public:
		void Update(GLFWwindow* window, Objects::GameObject* object) override;
		void Init(Objects::GameObject* object) override;
	};
}