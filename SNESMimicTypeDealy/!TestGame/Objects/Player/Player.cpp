#include "Player.h"
#include <memory>
#if _DEBUG
#include "../../../Debug/DebugLog.h"

#define PlayerLogger(x) (DEBUG::DebugLog::Log(x, true, ";34;44;1"))

#include "../../../Debug/LevelBuilder/LevelBuilder.h"
#endif

#include "../../../Utils/Time/GameTime.h"
#include "../../../Input/InputManager.h"
#include "../../../Rendering/DynamicSprite.h"

#include "../../TestGame.h"

#include <thread>

#define PLAYER_ANIMATION_RUN_WALK_SWITCH 180.f //When the player should switch from the walking to running animation.

namespace  GAME_NAME
{
	namespace  Objects
	{
		namespace Player
		{

			using namespace Utils;

			Player::Player(Vec2 position)
				: ActiveBoxCollisionGravityObject(position, Vec2(DefaultPlayerScaleX, DefaultPlayerScaleY), Rendering::Renderer::GetSprite(DefaultPlayerSprite))
			{
#if _DEBUG
				PlayerLogger("Initilized Player");
#endif

				//INIT WATER MUSIC
				Audio::SoundManager::WaterMusic = Audio::SoundManager::Play(Audio::UnderwaterMusicID, Audio::SoundManager::BGMusic, -1.0F, 0.0F, true);


#pragma region Init Run Animation
				AnimData walk_data, run_data, fall_data, jump_data, skid_data;

				for (int i : PlayerWalkAnim)
				{
					walk_data.Sprites.push_back(Renderer::GetSprite(i));
				}

				for (int i : PlayerRunAnim)
				{
					run_data.Sprites.push_back(Renderer::GetSprite(i));
				}

				for (int i : PlayerFallAnim)
				{
					fall_data.Sprites.push_back(Renderer::GetSprite(i));
				}

				for (int i : PlayerJumpAnim)
				{
					jump_data.Sprites.push_back(Renderer::GetSprite(i));
				}

				for (int i : PlayerSkidAnim)
				{
					skid_data.Sprites.push_back(Renderer::GetSprite(i));
				}

				std::shared_ptr<GAME_NAME::Components::Animation::Animation> walk_anim(new GAME_NAME::Components::Animation::Animation(walk_data, ANIM_12_SPF));
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> run_anim(new GAME_NAME::Components::Animation::Animation(run_data, ANIM_16_SPF));
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> fall_anim(new GAME_NAME::Components::Animation::Animation(fall_data, ANIM_12_SPF));
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> jump_anim(new GAME_NAME::Components::Animation::Animation(jump_data, ANIM_12_SPF));
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> skid_anim(new GAME_NAME::Components::Animation::Animation(skid_data, ANIM_12_SPF));

#pragma endregion

				std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ walk_anim, run_anim, fall_anim, jump_anim, skid_anim };

				m_animator = new AnimatorComponent(anims);

				m_physics->SetGravityStrength(DefaultPlayerGravity);

			}

			Player::~Player()
			{
				ActiveBoxCollisionGravityObject::~ActiveBoxCollisionGravityObject();
				delete m_animator;
			}

			
			int renderCalls = 0;
			float tAlloc = 0;
			float m_curr = 0;
			void Player::Update(GLFWwindow* window)
			{
				std::thread playerInput([this] { readKeys(); });

				std::thread animationUpdate([this, window] { m_animator->Update(window, this); });

#if _DEBUG
				if (!m_debug)
				{
					CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
				}
#else
				CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
#endif

			//DEBUGGING [REMOVE]
				{
					renderCalls++;
					float t = glfwGetTime();
					tAlloc += t - m_curr;
					m_curr = t;

					if (tAlloc > 1.f)
					{
						tAlloc = 0.f;
						std::cout << "PLAYER IN LAST SECOND: " << renderCalls << std::endl;
						renderCalls = 0;
					}
				}

				if (playerInput.joinable())
				{
					playerInput.join();
				}

				if (animationUpdate.joinable())
				{
					animationUpdate.join();
				}
			}

			void Player::SetSwimming(bool swimming)
			{
				m_swimming = swimming;
				if (m_swimming)
				{
					m_physics->SetVelocity(m_physics->GetVelocity() / 1.5f);
					m_physics->SetGravitationalVelocity(m_physics->GetGravitationalVelocity() / 1.3f);
					m_physics->SetGravityStrength(SwimmingPlayerGravity);
					m_physics->SetTerminalVelocity(0.04f);
					enableUnderwaterMusic();
				}
				else {
					m_physics->SetGravityStrength(DefaultPlayerGravity);
					m_physics->SetTerminalVelocity(240.f);
					m_physics->SetVelocity(m_physics->GetVelocity() / 1.5f);
					disableUnderwaterMusic();
				}
			}

			void Player::Render(const Vec2 cameraPosition)
			{
				if (m_swimming)
				{
					const double sin = (std::sin(glfwGetTime()) / 20.0);
					const double sin1 = (std::sin(glfwGetTime() * 1.1) / 20.0);
					const double sin2 = (std::sin(glfwGetTime() * 1.2) / 20.0);
					const double sin3 = (std::sin(glfwGetTime() * 1.3) / 20.0);

					Vec2 vertices[4]{
						Vec2(0.f + sin, 0.f),
						Vec2(0.f + sin1, 1.f),
						Vec2(1.f + sin2, 1.f),
						Vec2(1.f + sin3, 0.f)
					};
					
					DynamicSprite(m_sprite->GetSpriteId(), vertices).Render(cameraPosition, m_position + m_scale, m_scale, m_rotation + 180.f);
				}
				else {
					m_sprite->Render(cameraPosition, m_position + (m_textureFlipped ? (m_scale * Vec2::OneX) : 0), m_scale * (m_textureFlipped ? Vec2::MinusOneXOneY : 1), m_rotation);
				}
				
#if _DEBUG
				if (m_debug)
				{
					Debug::LevelBuilder::LevelBuilder::Render();
				}
#endif
			}

			void Player::onCollision(Vec2 push)
			{
				if (m_swimming) { return; }
				if (m_foundCollisionInTick) { return; }
				if (push.Y > 0)
				{
					m_onGround = true;
					m_foundCollisionInTick = true;
					m_physics->SetVelocityY(0.f);
				}
				
			}

			void Player::beforeCollision()
			{
				if (m_swimming) { return; }
				if (m_physics->GetGravitationalVelocity() < -m_physics->GetGravityStrength() - 1)
				{
					m_onGround = false;
				}
				m_foundCollisionInTick = false;
			}

			void Player::readKeys()
			{
				m_physics->SetFrictionDrag(Drag);

#if _DEBUG
				if (InputManager::GetKey(PLAYER_DEBUG))
				{
					if (!m_debugKey)
					{
						m_debug = !m_debug;
						m_debugKey = true;

						if (m_debug)
						{
							Debug::LevelBuilder::LevelBuilder::InitLevelBuilder(TestGame::INSTANCE);
							m_boxCollider->SetBeforeUpdate(nullptr);
							((GAME_NAME::Camera::GameCamera*)TestGame::INSTANCE->GetCamera())->SetFollowPlayerExact(true);
						}
						else {
							Debug::LevelBuilder::LevelBuilder::DestroyLevelBuilder();
							m_boxCollider->SetBeforeUpdate(beforeUpdate);
							((GAME_NAME::Camera::GameCamera*)TestGame::INSTANCE->GetCamera())->SetFollowPlayerExact(false);
						}
					}
				}
				else if (m_debugKey)
				{
					m_debugKey = false;
				}
#endif
				bool playerIsSkidding = false;

				//int joyAxesCount;		JOYSTICK INPUT
				//const float* joyAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &joyAxesCount);

				if (InputManager::GetKey(PLAYER_MOVE_RIGHT))
				{
#if _DEBUG
					if (m_debug)
					{
						m_position += Vec2(InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? 3.0f : 1.4f, 0.f);
						return;
					}
#endif
					if (m_physics->GetVelocity().X < PlayerSpeedCap)
					{
						m_physics->SetFrictionDrag(0);
						m_physics->AddVelocity(Vec2((PlayerSpeedCap - m_physics->GetVelocity().X) * (PlayerSpeed), 0.f));
						
						//Check if the player has begun to move to the right, play a sliding animation if slowing down, flip the sprite if moving right.
						if (m_physics->GetVelocity().X > 0)
						{
							m_textureFlipped = true;
						}
						else
						{
							playerIsSkidding = true;
						}
					}
				}

				if (InputManager::GetKey(PLAYER_MOVE_LEFT))
				{
#if _DEBUG
					if (m_debug)
					{
						m_position += Vec2(InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? -3.0f : -1.4f, 0.f);
						return;
					}
#endif
					if (m_physics->GetVelocity().X > -PlayerSpeedCap)
					{
						m_physics->SetFrictionDrag(0);
						m_physics->AddVelocity(Vec2((PlayerSpeedCap - m_physics->GetVelocity().X) * (-PlayerSpeed), 0.f));
					}

					//Check if the player has begun to move to the left, play a sliding animation if slowing down, flip the sprite if moving left.
					if (m_physics->GetVelocity().X < 0)
					{
						m_textureFlipped = false;
					}
					else
					{
						playerIsSkidding = true;
					}
				}


				{
					
//Determines what animation to play currently. (Move to seperate function. USE RETURNS INSTEAD OF ELSES)
					float anim_momentum;
					setAnimations(playerIsSkidding, anim_momentum);

					//Check if the user is holding the FORCE_WALK [Left Shift] key and damps the player's speed to 1/2 walking speed.
					if (InputManager::GetKey(PLAYER_FORCE_WALK))
					{
						if (anim_momentum > (PLAYER_ANIMATION_RUN_WALK_SWITCH/2))
						{
							m_physics->AddVelocity(Vec2(-m_physics->GetVelocity().NormalizeX() * (anim_momentum - (PLAYER_ANIMATION_RUN_WALK_SWITCH/2.f)) / 4.f, 0));
						}
					}
				}

#if _DEBUG
				if (m_debug)
				{
					if (InputManager::GetKey(PLAYER_MOVE_UP))
					{
						m_position += Vec2(0.f, InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? 3.0f : 1.4f);
					}

					if (InputManager::GetKey(PLAYER_MOVE_DOWN))
					{
						m_position += Vec2(0.f, InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? -3.0f : -1.4f);
					}
				}
#endif

				//Check if player is jumping.
				if (InputManager::GetKey(PLAYER_JUMP))
				{
					if (m_jumpHeld != 0 && m_jumpHeld < PlayerJumpHoldLength || m_swimming)
					{
						m_jumpHeld++;
						m_physics->AddVelocity(Vec2(0.f, PlayerJumpBonus));
					}

					if (m_onGround && !m_swimming)
					{
						//Jump Sound

						m_jumpHeld = 1;
						m_onGround = false;
						m_physics->AddVelocity(Vec2(0.f, PlayerJumpHeight));
					}
				}
				else if (m_jumpHeld != 0)
				{
					m_jumpHeld = 0;
				}
				


			}
			void Player::setAnimations(bool playerIsSkidding, float& anim_momentum)
			{
				anim_momentum = std::abs(m_physics->GetVelocity().X);	//X Speed of player.

				if (m_onGround)
				{
					if (playerIsSkidding && anim_momentum > 60.f)
					{
						m_animator->SetCurrentAnimation(4); //Skidding Animation
						return;
					}

					if (anim_momentum > 0.1f && m_onGround && !m_swimming)	//Check if player is moving a certain speed, is on the ground, and is not swimming.
					{
						m_animator->SetSpeedMult(anim_momentum / 100.f);
						if (anim_momentum > PLAYER_ANIMATION_RUN_WALK_SWITCH)
						{
							m_animator->SetCurrentAnimation(1);  //Running Animation
						}
						else {
							m_animator->SetCurrentAnimation(0);  //Walking Animation
						}
						m_begunMotion = true;
						return;
					}
					
					if (m_begunMotion)
					{
						m_animator->SetCurrentAnimation(-1); //No Animation
						m_sprite = Renderer::GetSprite(DefaultPlayerSprite);
						m_begunMotion = false;
					}
					return;
				}


				m_animator->SetSpeedMult(1.f);
				float player_y_vel = m_physics->GetVelocity().Y + m_physics->GetGravitationalVelocity();

				if (player_y_vel > 1.f)
				{
					m_animator->SetCurrentAnimation(3); //Jumping Animation
					m_begunMotion = true;
					return;
				}
				
				if (player_y_vel < -1.f)
				{
					m_animator->SetCurrentAnimation(2); //Falling Animation
					m_begunMotion = true;
					return;
				}
			}
		}
	}
}