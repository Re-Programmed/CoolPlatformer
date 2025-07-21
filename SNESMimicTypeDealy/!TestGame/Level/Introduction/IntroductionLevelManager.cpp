#include "IntroductionLevelManager.h"

#include "../../TestGame.h"

#include "../../../Objects/GUI/Menus/GUIMenu.h"
#include "../../../Utils/Time/GameTime.h"

#include "../../Cutscenes/DialogueManager.h"

#include "../../../Objects/Tags/ObjectTagManager.h"

#include "../../Mappings.h"

using namespace GAME_NAME::Cutscenes;

constexpr const char* INTROMNGR_INTRO_DIALOGUE = "OutOfBed";

#define ROOM_COLLIDERS_TAG "RoomCollision"

constexpr unsigned int INTROMNGR_PULLEY_SPRITE = 31;
constexpr unsigned int INTROMNGR_ROPE_SPRITE = 30;
constexpr unsigned int INTROMNGR_SLANT_SHELF_SPRITE = 36;
constexpr unsigned int INTROMNGR_ROPE_BOARD_SPRITE = 35;
constexpr unsigned int INTROMNGR_BALL_SPRITE = 47;
constexpr unsigned int INTROMNGR_BOOK_FIRST_SPRITE = 37, INTROMNGR_BOOK_LAST_SPRITE = 42;
constexpr unsigned int INTROMNGR_LEVER_SPRITE = 44, INTROMNGR_LEVER_UP_SPRITE = 45;

namespace GAME_NAME::Level
{
	IntroductionLevelManager::IntroductionLevelManager()
	{
		TestGame::ThePlayer->HideAllUI();
		//Fix camera to go to where the player is, for some reason the player is starting too far away and the camera gets stuck.
		TestGame::INSTANCE->GetCamera()->SetPosition(TestGame::ThePlayer->GetPosition() - Vec2{ TargetResolutionX, TargetResolutionY } / 2.f);
		
		//Freeze and hide the player.
		//TestGame::ThePlayer->SetEnableRendering(false);
		//TestGame::ThePlayer->SetFrozen(true);

		createRube();
	}


    void IntroductionLevelManager::Update(GLFWwindow* window)
    {
		if (m_rubeTimer < -2)
		{
			//Second room.
			TestGame::INSTANCE->ThePlayer->SetControlType(Objects::Player::Player::ControlType::ROOM);

			return;
		}

        executeRube();
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

	inline void  IntroductionLevelManager_toggleRoomColliders(bool enabled)
	{
		auto[begin, end] = Tags::ObjectTagManager::GetObjectsWithTag(ROOM_COLLIDERS_TAG);

		for (begin; begin != end; ++begin)
		{
			StaticBoxCollisionObject* collider = dynamic_cast<StaticBoxCollisionObject*>(begin->second);
			collider->SetEnabled(enabled);
		}
	}

	void IntroductionLevelManager::createRube()
	{
		IntroductionLevelManager_toggleRoomColliders(false);
		
		//TESTING
		m_rubeTimer = -9999;

		return;

		AnimData bed_data;
		for(int i = 56; i <= 62; i++){ bed_data.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(i))); }
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> bed_anim = std::shared_ptr<GAME_NAME::Components::Animation::Animation>(new GAME_NAME::Components::Animation::Animation(bed_data, ANIM_12_SPF));
		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> bed_anims{ bed_anim };
		AnimatorComponent* bed_ac = new AnimatorComponent(bed_anims);

		//0,1103,115,-58,32,24,1
		m_rubeBed = new ComponentObject(Vec2{ 1103, 115 }, Vec2{ -58, 70 }, Renderer::GetSprite(56), std::vector<IComponent*>{ bed_ac });
		Renderer::LoadObject(m_rubeBed);

		//0,1030,129,11,8,27,2
		m_rubeClock = new GameObject(Vec2{ 1030, 129 }, Vec2{ 11, 8 }, Renderer::GetSprite(27));
		Renderer::LoadObject(m_rubeClock, 2);

		//Ball release pulleys.
		m_rubePulleys[0] = createPulley(Vec2{ 1026, 161 }, Vec2{ 8, 10 });
		m_rubePulleys[1] = createPulley(Vec2{ 982, 161 }, Vec2{ -8, 10 });

		//Falling ball pulleys.
		m_rubePulleys[2] = createPulley(Vec2{ 1071, 161 }, Vec2{ -8, 10 });
		m_rubePulleys[3] = createPulley(Vec2{ 1088, 161 }, Vec2{ 8, 10 });

		m_rubeRopes[0] = new GameObject(Vec2{ 1033,135 }, Vec2{ 1, 26 }, Renderer::GetSprite(INTROMNGR_ROPE_SPRITE));
		Renderer::LoadObject(m_rubeRopes[0], 1, true);

		m_rubeRopes[1] = new GameObject(Vec2{ 982, 168 }, Vec2{ 46, 1 }, Renderer::GetSprite(INTROMNGR_ROPE_SPRITE));
		Renderer::LoadObject(m_rubeRopes[1], 1, true);
		m_rubeRopes[1]->RotateAboutCenter(90.f);

		m_rubeSlantedShelf = new GameObject(Vec2{ 967, 143 }, Vec2{ 64, 11 }, Renderer::GetSprite(INTROMNGR_SLANT_SHELF_SPRITE));
		Renderer::LoadObject(m_rubeSlantedShelf, 1);

		m_rubeRopeBoard = new GameObject(Vec2{ 972, 148 }, Vec2{ 6, 13 }, Renderer::GetSprite(INTROMNGR_ROPE_BOARD_SPRITE));
		Renderer::LoadObject(m_rubeRopeBoard, 1, true);

		m_rubeBall = new ActiveBoxCollisionGravityObject(Vec2{ 968, 149.5f }, Vec2{ 4, 4 }, Renderer::GetSprite(INTROMNGR_BALL_SPRITE));
		m_rubeBall->GetPhysics()->SetGravityStrength(0);
		Renderer::LoadObject(m_rubeBall);

		AnimData book_animation;
		for (int i = INTROMNGR_BOOK_FIRST_SPRITE; i <= INTROMNGR_BOOK_LAST_SPRITE; i++) { book_animation.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(i))); }
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> book_anim = std::shared_ptr<GAME_NAME::Components::Animation::Animation>(new GAME_NAME::Components::Animation::Animation(book_animation, ANIM_12_SPF));
		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ book_anim };
		AnimatorComponent* book_ac = new AnimatorComponent(anims);

		m_rubeBlueBook1 = new ComponentObject(Vec2{ 1042, 145 }, Vec2{ -16, 16 }, Renderer::GetSprite(INTROMNGR_BOOK_FIRST_SPRITE), std::vector<IComponent*>{ book_ac });
		Renderer::LoadObject(m_rubeBlueBook1, 2);
		//(dynamic_cast<AnimatorComponent*>(m_rubeBlueBook1->GetComponent(0)))->SetAllowLooping(false);

		m_rubeLever = new GameObject(Vec2{ 1038, 146 }, Vec2{ 16, 4 }, Renderer::GetSprite(INTROMNGR_LEVER_SPRITE));
		Renderer::LoadObject(m_rubeLever);


		AnimData ball_launch_animation;
		for (int i = 48; i <= 55; i++) { ball_launch_animation.Sprites.emplace_back(std::shared_ptr<Sprite>(Renderer::GetSprite(i))); }
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> ball_launch_anim = std::shared_ptr<GAME_NAME::Components::Animation::Animation>(new GAME_NAME::Components::Animation::Animation(ball_launch_animation, ANIM_6_SPF));
		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> ball_anims{ ball_launch_anim };
		AnimatorComponent* ball_ac = new AnimatorComponent(ball_anims);

		m_smallBallLaunch = new ComponentObject(Vec2{ 1072, 131 }, Vec2{ -24, 38 }, Renderer::GetSprite(INTROMNGR_BALL_SPRITE + 1), std::vector<IComponent*>{ ball_ac });
		Renderer::LoadObject(m_smallBallLaunch);

		/*
		; First shelf collision (17,13,19,15)
			2,967,143,17,5,1,0
			2,984,143,13,4,1,0
			2,997,143,19,3,1,0
			2,1016,143,15,2,1,0
		*/
		m_shelfColliders[0] = new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(Vec2{ 967, 143 }, Vec2{ 17, 5 }, Renderer::GetSprite(1)); Renderer::LoadObject(m_shelfColliders[0], 0);
		m_shelfColliders[1] = new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(Vec2{ 984, 143 }, Vec2{ 13, 4 }, Renderer::GetSprite(1)); Renderer::LoadObject(m_shelfColliders[1], 0);
		m_shelfColliders[2] = new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(Vec2{ 997, 143 }, Vec2{ 19, 3 }, Renderer::GetSprite(1)); Renderer::LoadObject(m_shelfColliders[2], 0);
		m_shelfColliders[3] = new GAME_NAME::Components::Physics::Collision::StaticBoxCollisionObject(Vec2{ 1016, 143 }, Vec2{ 15, 2 }, Renderer::GetSprite(1)); Renderer::LoadObject(m_shelfColliders[3], 0);
	}

	

	void IntroductionLevelManager::executeRube()
	{
		double dTime = Utils::Time::GameTime::GetScaledDeltaTime();
		m_rubeTimer += dTime;

		std::cout << m_rubeTimer << std::endl;

		if (m_rubeTimer > 5.0 && m_rubeTimer <= 9.6)
		{
			//Ring clock.
			m_rubeSubTimer += dTime;
			if (m_rubeSubTimer > 0.075)
			{
				m_rubeSubTimer = 0;
				ilm_rube_flag = !ilm_rube_flag;
				m_rubeClock->Translate(Vec2{ ilm_rube_flag ? 0.6f : -0.6f, 0 });
			}

			return;
		}

		if (m_rubeTimer > 9.6 && m_rubeTimer < 11.5)
		{
			ilm_rube_flag = false;
			return;
		}

		if (m_rubeTimer > 11.55 && m_rubeTimer < 17.0)
		{
			if (!ilm_rube_flag)
			{
				ilm_rube_flag = true;

				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[0]->GetComponent(0)))->SetSpeedMult(-0.075);
				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[1]->GetComponent(0)))->SetSpeedMult(0.075);

				for (int i = 0; i < 2; i++)
				{
					Components::ComponentObject*& pulley = m_rubePulleys[i];
					(dynamic_cast<AnimatorComponent*>(pulley->GetComponent(0)))->SetCurrentAnimation(0);
				}
			}

			if (m_rubeTimer > 13.0)
			{
				m_rubeRopeBoard->Translate(Vec2{ 0, static_cast<float>(dTime) * 1.2f });
			}

			return;
		}

		if (m_rubeTimer > 17.0 && m_rubeTimer < 30.0)
		{
			if (ilm_rube_flag)
			{
				ilm_rube_flag = false;
				for (int i = 0; i < 2; i++)
				{
					Components::ComponentObject*& pulley = m_rubePulleys[i];
					(dynamic_cast<AnimatorComponent*>(pulley->GetComponent(0)))->SetCurrentAnimation(-1);
				}

				m_rubeBall->GetPhysics()->SetGravityStrength(1.f);
				m_rubeBall->GetPhysics()->SetVelocityX(12.f);
				m_rubeBall->GetPhysics()->SetFrictionDrag(0.f);

			}

			m_rubeBall->GetPhysics()->SetVelocityX(10.f);
			m_rubeBall->RotateAboutCenter(-1.2f);
			
			if ((m_rubeBlueBook1->GetPosition().X + m_rubeBlueBook1->GetScale().X) - m_rubeBall->GetPosition().X < 3.f)
			{
				m_rubeTimer = 30.0;
			}

			return;
		}

		if (m_rubeTimer > 30.0 && m_rubeTimer < 30.5)
		{
			if (!ilm_rube_flag)
			{
				ilm_rube_flag = true;

				m_rubeBall->GetPhysics()->SetVelocityX(0.f);
				m_rubeBall->GetPhysics()->SetTerminalVelocity(0.f);
				m_rubeBall->GetPhysics()->SetGravityStrength(0.f);

				(dynamic_cast<AnimatorComponent*>(m_rubeBlueBook1->GetComponent(0)))->SetAllowLooping(false);
				(dynamic_cast<AnimatorComponent*>(m_rubeBlueBook1->GetComponent(0)))->SetCurrentAnimation(0, m_rubeBlueBook1);
			}

			return;
		}

		if (m_rubeTimer > 30.5 && m_rubeTimer < 31.5)
		{
			if (ilm_rube_flag)
			{
				ilm_rube_flag = false;

				m_rubeLever->SetSprite(Renderer::GetSprite(INTROMNGR_LEVER_UP_SPRITE));
				(dynamic_cast<AnimatorComponent*>(m_smallBallLaunch->GetComponent(0)))->SetAllowLooping(false);
				(dynamic_cast<AnimatorComponent*>(m_smallBallLaunch->GetComponent(0)))->SetCurrentAnimation(0, m_smallBallLaunch);

				//Start pulley spinning.
				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[2]->GetComponent(0)))->SetSpeedMult(0.066);
				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[2]->GetComponent(0)))->SetCurrentAnimation(0);

				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[3]->GetComponent(0)))->SetSpeedMult(0.066);
				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[3]->GetComponent(0)))->SetCurrentAnimation(0);

				//Bed launches.
				(dynamic_cast<AnimatorComponent*>(m_rubeBed->GetComponent(0)))->SetAllowLooping(false);
				(dynamic_cast<AnimatorComponent*>(m_rubeBed->GetComponent(0)))->SetCurrentAnimation(0, m_rubeBed);

				//Make room for player to fly.
				Renderer::DestroyObject(m_shelfColliders[0]);
				Renderer::DestroyObject(m_shelfColliders[1]);
				Renderer::DestroyObject(m_shelfColliders[2]);
				Renderer::DestroyObject(m_shelfColliders[3]);
			}
		
		}

		if (m_rubeTimer > 30.81 && m_rubeTimer < 32.08)
		{
			if (ilm_player_flying == nullptr)
			{
				//Create flying player.
				ilm_player_flying = new ActiveBoxCollisionGravityObject(Vec2{ 1089, 138 }, Vec2{ -45.f / 1.75f, 41.f / 1.75f }, Renderer::GetSprite(SpriteBase(232)));
				ilm_player_flying->GetPhysics()->SetGravityStrength(2.f);
				ilm_player_flying->GetPhysics()->AddVelocity(Vec2{ -190.f, 20.f });
				Renderer::InstantiateObject(Renderer::InstantiateGameObject(ilm_player_flying, true, 2, false));
			}

			//Player struggling while flying animation.
			m_rubeSubTimer += dTime;
			if (m_rubeSubTimer > 0.075)
			{
				m_rubeSubTimer = 0;
				ilm_player_flying->SetSprite(Renderer::GetSprite(ilm_rube_flag_2 ? SpriteBase(231) : SpriteBase(232)));
				ilm_rube_flag_2 = !ilm_rube_flag_2;
			}
		}

		if (m_rubeTimer > 31.81 && m_rubeTimer < 32.08)
		{
			if (!ilm_rube_flag)
			{
				ilm_rube_flag = true;

				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[2]->GetComponent(0)))->SetCurrentAnimation(-1);
				(dynamic_cast<AnimatorComponent*>(m_rubePulleys[3]->GetComponent(0)))->SetCurrentAnimation(-1);

				ilm_player_flying->GetPhysics()->SetVelocity(Vec2::Zero);
				ilm_player_flying->GetPhysics()->SetGravityStrength(0.f);
			}

			return;
		}

		//Player is splatted on the floor...
		if (m_rubeTimer > 32.08 && m_rubeTimer < 35.44)
		{
			if (ilm_rube_flag)
			{
				ilm_rube_flag = false;

				ilm_player_flying->SetScale(Vec2{ 26, 26 });
				ilm_player_flying->SetPosition(ilm_player_flying->GetPosition() + Vec2{ -29, 0 });
				ilm_player_flying->SetSprite(Renderer::GetSprite(GAME_NAME::Objects::Player::Player::TextureData[GAME_NAME::Objects::Player::Player::DEFAULT_BIRB].Fall));
			}
		}

#define FallenSprite GAME_NAME::Objects::Player::Player::TextureData[GAME_NAME::Objects::Player::Player::DEFAULT_BIRB].Fall + 4

		if (m_rubeTimer > 35.44 && m_rubeTimer < 36.5)
		{
			if (!ilm_rube_flag)
			{
				ilm_player_flying->SetSprite(Renderer::GetSprite(FallenSprite));
				ilm_rube_flag = true;
			}
			else {
				m_rubeSubTimer += dTime;
				if (m_rubeSubTimer > 0.215)
				{
					if (ilm_player_flying->GetSprite()->GetSpriteId() < FallenSprite + 5 + (-SpriteBase(0)))
					{
						ilm_player_flying->SetSprite(new Sprite(ilm_player_flying->GetSprite()->GetSpriteId() + 1));
					}

					m_rubeSubTimer = 0;
				}
			}

			return;
		}

		if (m_rubeTimer > 36.5)
		{
			if (!ilm_rube_flag) { return; }
			ilm_rube_flag = false;

			Renderer::DestroyActiveObject(ilm_player_flying);
			
			TestGame::ThePlayer->SetPosition(ilm_player_flying->GetPosition() + Vec2{ 7.25f, 0.f });
			TestGame::ThePlayer->SetEnableRendering(true);
			TestGame::ThePlayer->SetFrozen(false);

			TestGame::ThePlayer->SetControlType(Objects::Player::Player::ControlType::ROOM);

			GUI::Menus::GUIMenu::OpenMenu();
			DialogueManager::INSTANCE->PlayDialogueSequence(DialogueManager::INSTANCE->GetDialogueSequence(INTROMNGR_INTRO_DIALOGUE));

			m_rubeBed->SetSprite(Renderer::GetSprite(64)); //Bed Empty Sprite
			IntroductionLevelManager_toggleRoomColliders(true);

			m_rubeTimer = -9999;
		}
	}
}

