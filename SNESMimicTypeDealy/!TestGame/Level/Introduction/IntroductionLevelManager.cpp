#include "IntroductionLevelManager.h"

#include "../../TestGame.h"

constexpr unsigned int INTROMNGR_PULLEY_SPRITE = 31;
constexpr unsigned int INTROMNGR_ROPE_SPRITE = 30;
constexpr unsigned int INTROMNGR_SLANT_SHELF_SPRITE = 36;
constexpr unsigned int INTROMNGR_ROPE_BOARD_SPRITE = 35;
constexpr unsigned int INTROMNGR_BALL_SPRITE = 47;
constexpr unsigned int INTROMNGR_BOOK_FIRST_SPRITE = 37, INTROMNGR_BOOK_LAST_SPRITE = 42;
constexpr unsigned int INTROMNGR_LEVER_SPRITE = 44;

namespace GAME_NAME::Level
{
	IntroductionLevelManager::IntroductionLevelManager()
	{
		TestGame::ThePlayer->HideAllUI();
		TestGame::INSTANCE->GetCamera()->SetPosition(TestGame::ThePlayer->GetPosition() - Vec2{ TargetResolutionX, TargetResolutionY } / 2.f);

		createRube();
	}

	void IntroductionLevelManager::Update(GLFWwindow* window)
	{
	}

	inline Components::ComponentObject* createPulley(Vec2 position, Vec2 scale)
	{
		AnimData data;
		data.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(INTROMNGR_PULLEY_SPRITE)));
		data.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(INTROMNGR_PULLEY_SPRITE + 1)));
		data.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(INTROMNGR_PULLEY_SPRITE + 2)));
		data.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(INTROMNGR_PULLEY_SPRITE + 3)));
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> anim = std::shared_ptr<GAME_NAME::Components::Animation::Animation>(new GAME_NAME::Components::Animation::Animation(data, ANIM_12_SPF));

		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ anim };
		AnimatorComponent* ac = new AnimatorComponent(anims);

		Components::ComponentObject* pulley = new Components::ComponentObject(position, scale, Renderer::GetSprite(INTROMNGR_PULLEY_SPRITE), std::vector<IComponent*>{ ac });
		Renderer::LoadObject(pulley, 1, true);

		return pulley;
	}

	void IntroductionLevelManager::createRube()
	{
		m_rubePulleys[0] = createPulley(Vec2{ 1026, 161 }, Vec2{ 8, 10 });
		m_rubePulleys[1] = createPulley(Vec2{ 982, 161 }, Vec2{ -8, 10 });

		m_rubeRopes[0] = new GameObject(Vec2{ 1033,135 }, Vec2{ 1, 26 }, Renderer::GetSprite(INTROMNGR_ROPE_SPRITE));
		Renderer::LoadObject(m_rubeRopes[0], 1, true);

		m_rubeRopes[1] = new GameObject(Vec2{ 982, 168 }, Vec2{ 46, 1 }, Renderer::GetSprite(INTROMNGR_ROPE_SPRITE));
		Renderer::LoadObject(m_rubeRopes[1], 1, true);
		m_rubeRopes[1]->RotateAboutCenter(90.f);

		m_rubeSlantedShelf = new GameObject(Vec2{ 967, 143 }, Vec2{ 64, 11 }, Renderer::GetSprite(INTROMNGR_SLANT_SHELF_SPRITE));
		Renderer::LoadObject(m_rubeSlantedShelf, 1);

		m_rubeRopeBoard = new GameObject(Vec2{ 972, 148 }, Vec2{ 6, 13 }, Renderer::GetSprite(INTROMNGR_ROPE_BOARD_SPRITE));
		Renderer::LoadObject(m_rubeRopeBoard, 1, true);

		m_rubeBall = new GameObject(Vec2{ 968, 149.5f }, Vec2{ 4, 4 }, Renderer::GetSprite(INTROMNGR_BALL_SPRITE));
		Renderer::LoadObject(m_rubeBall);

		AnimData book_animation;
		for (int i = INTROMNGR_BOOK_FIRST_SPRITE; i <= INTROMNGR_BOOK_LAST_SPRITE; i++) { book_animation.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(i))); }
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> book_anim = std::shared_ptr<GAME_NAME::Components::Animation::Animation>(new GAME_NAME::Components::Animation::Animation(book_animation, ANIM_12_SPF));
		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ book_anim };
		AnimatorComponent* book_ac = new AnimatorComponent(anims);

		m_rubeBlueBook1 = new ComponentObject(Vec2{ 1040, 145 }, Vec2{ -16, 16 }, Renderer::GetSprite(INTROMNGR_BOOK_FIRST_SPRITE), std::vector<IComponent*>{ book_ac });
		Renderer::LoadObject(m_rubeBlueBook1);
		//(dynamic_cast<AnimatorComponent*>(m_rubeBlueBook1->GetComponent(0)))->SetAllowLooping(false);

		m_rubeLever = new GameObject(Vec2{ 1040, 146 }, Vec2{ 16, 4 }, Renderer::GetSprite(INTROMNGR_LEVER_SPRITE));
		Renderer::LoadObject(m_rubeLever);
	}
}

