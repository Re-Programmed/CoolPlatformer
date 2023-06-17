#include "Player.h"
#include <memory>
#if _DEBUG
#include "../../../Debug/DebugLog.h"

#define PlayerLogger(x) (DEBUG::DebugLog::Log(x, true, ";34;44;1"))
#endif

#include "../../../Utils/Time/GameTime.h"
#include "../../../Input/InputManager.h"
#include "../../../Rendering/DynamicSprite.h"

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

				AnimData data;
				data.Sprites.push_back(Renderer::GetSprite(1));
				data.Sprites.push_back(Renderer::GetSprite(4));
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> anim(new GAME_NAME::Components::Animation::Animation(data, 0.5f));

				std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ anim };

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
				m_animator->Update(window, this);

#if _DEBUG
				if (!m_debug)
				{
					CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
				}
#else
				CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
#endif
				readKeys();

	
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
					m_sprite->Render(cameraPosition, m_position, m_scale, m_rotation);
				}
				
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
							m_boxCollider->SetBeforeUpdate(nullptr);
						}
						else {
							m_boxCollider->SetBeforeUpdate(beforeUpdate);
						}
					}
				}
				else if (m_debugKey)
				{
					m_debugKey = false;
				}
#endif

				if (InputManager::GetKey(PLAYER_MOVE_RIGHT))
				{

#if _DEBUG
					if (m_debug)
					{
						m_position += Vec2(1.4f, 0.f);
						return;
					}
#endif

					if (m_physics->GetVelocity().X < PlayerSpeedCap)
					{
						m_physics->SetFrictionDrag(0);
						m_physics->AddVelocity(Vec2((PlayerSpeedCap - m_physics->GetVelocity().X) * PlayerSpeed, 0.f));
					}
				}

				if (InputManager::GetKey(PLAYER_MOVE_LEFT))
				{
#if _DEBUG
					if (m_debug)
					{
						m_position += Vec2(-1.4f, 0.f);
						return;
					}
#endif

					if (m_physics->GetVelocity().X > -PlayerSpeedCap)
					{
						m_physics->SetFrictionDrag(0);
						m_physics->AddVelocity(Vec2((PlayerSpeedCap - m_physics->GetVelocity().X) * -PlayerSpeed, 0.f));
					}
				}

#if _DEBUG
				if (m_debug)
				{
					if (InputManager::GetKey(PLAYER_MOVE_UP))
					{
						m_position += Vec2(0.f, 1.4f);
					}

					if (InputManager::GetKey(PLAYER_MOVE_DOWN))
					{
						m_position += Vec2(0.f, -1.4f);
					}
				}
#endif

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
		}
	}
}