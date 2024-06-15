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
#include "../../../Objects/GUI/Menus/GUIMenu.h"

#include "../../../Objects/Instantiate/LevelObjectHandler.h"

#include "../../TestGame.h"

#include "../../Items/FloorItem.h"

#include <thread>

#define PLAYER_ANIMATION_RUN_WALK_SWITCH 180.f //When the player should switch from the walking to running animation.

namespace  GAME_NAME
{
	namespace  Objects
	{
		namespace Player
		{
			typedef int8_t PlayerEmotion;
			
			enum PLAYER_EMOTIONS : PlayerEmotion
			{
				ANGRY = SpriteBase(26)
			};

			using namespace Utils;

			Player::Player(Vec2 position)
				: ActiveBoxCollisionGravityObject(position, Vec2(DefaultPlayerScaleX, DefaultPlayerScaleY), Rendering::Renderer::GetSprite(DefaultPlayerSprite)), m_screenInventory(new ScreenInventory()),
				m_healthProgressBar(new ProgressBar(
					Vec2(2, 10), Vec2(64, 16), Renderer::GetSprite(SpriteBase(72))->GetSpriteId()
				)),
				MiscStateGroup("pl"), m_saveState(new PlayerSaveState(this)),
				m_particleEmitter(new Particles::ParticleEmitter(position))
			{
#if _DEBUG
				PlayerLogger("Initilized Player");
#endif
				m_particleEmitter->SetScale(m_scale);

				//INIT WATER MUSIC
				Audio::SoundManager::WaterMusic = Audio::SoundManager::Play(Audio::UnderwaterMusicID, Audio::SoundManager::BGMusic, -1.0F, 0.0F, true);

				//Load the stat overlay menu that contains sprites for health and inventory.
				GUI::Menus::GUIMenu::LoadMenu("/stat_overlay", nullptr);
				Renderer::LoadGUIElement(m_healthProgressBar, 0);

				//Register animations

#pragma region Init Animation
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

				m_emotionsObject = new ChildGameObject(Vec2(DefaultPlayerScaleX, 12.25), Vec2(-DefaultPlayerScaleX, DefaultPlayerScaleY * 0.519230769f), Renderer::GetSprite(PLAYER_EMOTIONS::ANGRY), this);
				//Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_emotionsObject, true, 2, false));

				m_heldItemDisplay = nullptr;

				std::shared_ptr<std::vector<std::string>> states = this->getStates();

				if (states->size() > 0)
				{
					decodeSave(states->at(0));
				}

				assignState(m_saveState);
			}

			Player::~Player()
			{
				ActiveBoxCollisionGravityObject::~ActiveBoxCollisionGravityObject();
				delete m_animator;
				delete m_saveState;
				delete m_heldItemDisplay;
			}

			
			int renderCalls = 0;
			float tAlloc = 0;
			float m_curr = 0;
			void Player::Update(GLFWwindow* window)
			{
				std::thread playerInput([this] { readKeys(); });

				std::thread animationUpdate([this, window] { m_animator->Update(window, this); });

				

				//This makes the current held item move up and down while running to look like it is moving around in the player's hand.
				if (m_heldItemDisplay != nullptr && m_heldItemDisplay->GetScale().X != 0)
				{
					if (m_heldItemDisplay->GetScale().X < 8)
					{
						float add = std::sin(m_position.X / 8.f) * 1.44f;
						m_heldItemDisplay->SetPosition(m_position + Vec2(2, 3 + (add)));
					}

				}

				//Calculate time spent in air.
				if (!m_onGround)
				{
					m_airTime += Time::GameTime::GetScaledDeltaTime();
				}

				//Update the health bar display.
				m_healthProgressBar->SetPercentage(m_stats.Health);

#if _DEBUG
				if (!m_flight)
				{
					CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
				}
#else
				CollisionManager::RegisterActiveColliderToBuffer(m_boxCollider);
#endif


				if (playerInput.joinable())
				{
					playerInput.join();
				}

				if (animationUpdate.joinable())
				{
					animationUpdate.join();
				}

				m_screenInventory->Update();
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


			void Player::Render(const Vec2& cameraPosition)
			{
#if _DEBUG
				if (m_debug)
				{
					Debug::LevelBuilder::LevelBuilder::Render();
				}
#endif

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
					return;
				}
				else {
					m_sprite->Render(cameraPosition, m_position + (m_textureFlipped ? (m_scale * Vec2::OneX) : 0), m_scale * (m_textureFlipped ? Vec2::MinusOneXOneY : 1), m_rotation);
				}

				/*
					Held item rendering.
				*/

				if (m_heldItemDisplay != nullptr && m_heldItemDisplay->GetScale().X > 8)
				{
					const float playerYVel = m_physics->GetVelocity().Y + m_physics->GetGravitationalVelocity();
					if (playerYVel > 1.5f && !m_onGround)
					{
						const int baseSpriteId = m_heldItemDisplay->GetSprite()->GetSpriteId() - m_heldItemDisplayFrameOffset;
						const int frame = 0;
						m_heldItemLastSprite = new Sprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						m_heldItemDisplay->SetPosition(m_position + (m_textureFlipped ? Vec2(6.75f, -0.5f) : Vec2(0, -0.5f)));
					}else if (playerYVel < -1.5f && !m_onGround)
					{
						const int baseSpriteId = m_heldItemDisplay->GetSprite()->GetSpriteId() - m_heldItemDisplayFrameOffset;
						const int frame = 2;
						m_heldItemLastSprite = new Sprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						m_heldItemDisplay->SetPosition(m_position + (m_textureFlipped ? Vec2(2.6f, 7.f) : Vec2(4.5f, 7.f)));
					}
					else if (m_physics->GetVelocity().X > 0.3 || m_physics->GetVelocity().X < -0.3)
					{
						int&& frame = m_animator->GetCurrentAnimation()->GetFrame();
						int baseSpriteId = m_heldItemDisplay->GetSprite()->GetSpriteId() - m_heldItemDisplayFrameOffset;

						//Determine what frame of item animation to show.
						switch (frame)
						{
						case 0:
							frame = 0;
							break;
						case 1:
							frame = 1;
							break;
						case 2:
							frame = 2;
							break;
						case 3:
							frame = 1;
							break;
						case 4:
							frame = 0;
							break;
						case 5:
							frame = 3;
							break;
						case 6:
							frame = 4;
							break;
						case 7:
							frame = 3;
							break;
						}

						m_heldItemLastSprite = new Sprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						m_heldItemDisplay->SetPosition(m_position + (m_textureFlipped ? Vec2(6.75f, -0.5f) : Vec2(0, -0.5f)));
					}
					else {
						if (m_heldItemDisplayFrameOffset != 0)
						{
							m_heldItemDisplay->SetSprite(new Sprite(m_heldItemDisplay->GetSprite()->GetSpriteId() - m_heldItemDisplayFrameOffset));
							m_heldItemDisplayFrameOffset = 0;
						}
						m_heldItemDisplay->SetPosition(m_position + Vec2(3.5, 0.95f));
					}

					if (m_textureFlipped)
					{
						m_heldItemDisplay->GetSprite()->Render(cameraPosition, m_heldItemDisplay->GetPosition() + Vec2{ m_heldItemDisplay->GetScale().X - 7, 0 }, m_heldItemDisplay->GetScale() * Vec2{ -1, 1 }, 0.0F);
					}
					else {
						m_heldItemDisplay->GetSprite()->Render(cameraPosition, m_heldItemDisplay->GetPosition(), m_heldItemDisplay->GetScale(), 0.0F);
					}
				}
			}

#if _DEBUG
			void Player::EnterDebug()
			{
				m_debug = !m_debug;

				if (m_debug)
				{
					Debug::LevelBuilder::LevelBuilder::InitLevelBuilder(TestGame::INSTANCE);			
				}
				else
				{
					Debug::LevelBuilder::LevelBuilder::DestroyLevelBuilder();
				}
			}

			void Player::ToggleFlight()
			{
				{
					m_flight = !m_flight;

					if (m_flight)
					{
						m_boxCollider->SetBeforeUpdate(nullptr);
						((GAME_NAME::Camera::GameCamera*)TestGame::INSTANCE->GetCamera())->SetFollowPlayerExact(true);
					}
					else
					{
						m_boxCollider->SetBeforeUpdate(beforeUpdate);
						((GAME_NAME::Camera::GameCamera*)TestGame::INSTANCE->GetCamera())->SetFollowPlayerExact(false);
					}
				}
			}

#endif

			void Player::Damage(float damage)
			{
				CreateBloodParticle();
				m_stats.Health -= damage;
				m_healthProgressBar->SetPercentage(m_stats.Health);

				if (m_stats.Health <= 0)
				{
					Kill();
				}
			}

			void Player::Kill()
			{

			}

			//Sets the display for the held item/tool.
			void Player::SetHeldItem(Items::InventoryItem* item)
			{
				//If no display exists yet, create one.
				if (m_heldItemDisplay == nullptr)
				{
					m_heldItemDisplay = new GameObject(m_position, Vec2(0), Renderer::GetSprite(0));
					//Renderer::LoadActiveObject(m_heldItemDisplay, 2); NOT NEEDED SINCE THE HELD ITEM IS RENDERED THROUGH THE PLAYER RENDERER.
				}

				//Update item position, scale, and sprite.
				m_heldItemDisplay->SetPosition(m_position + Vec2(2, 3));
				m_heldItemDisplay->SetScale(Vec2(8));


				//If the item has a custom display.
				const int& customHeldTexture = Items::ITEM_DATA[item->GetType()].HeldTexture;

				if (customHeldTexture != GLOBAL_SPRITE_BASE)
				{
					m_heldItemDisplay->SetScale({ 16, 16 });
					//delete m_heldItemDisplay->GetSprite();

					std::cout << "FOUND CUSTOM ITEM HOLD DISPLAY" << customHeldTexture << "\n";

					m_heldItemDisplay->SetSprite(Renderer::GetSprite(customHeldTexture));
					return;
				}

				m_heldItemDisplay->SetSprite(Items::ITEMTYPE_GetItemTypeTexture(item->GetType()));
			}

#define COLLISION_VEL_STOP_DAMPING 0.1f

			void Player::onCollision(Vec2 push)
			{
				if (m_swimming) { return; }
				if (m_foundCollisionInTick) { return; }
				if (push.Y > 0)
				{
					m_isFlying = false;
					m_onGround = true;
					m_foundCollisionInTick = true;
					m_physics->SetVelocityY(0.f);

					//Calculate fall damage.
					if (m_airTime > 1.85f)
					{
						std::cout << m_airTime << std::endl;

						Damage((m_airTime - 1.85f) * 10.f);
					}

					m_airTime = 0;
				}

				if (push.X > COLLISION_VEL_STOP_DAMPING || push.X < -COLLISION_VEL_STOP_DAMPING)
				{
					m_physics->SetVelocityX(0);
				}

				if (push.Y > COLLISION_VEL_STOP_DAMPING || push.Y < -COLLISION_VEL_STOP_DAMPING)
				{
					m_physics->SetVelocityY(0);
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

			void Player::decodeSave(const std::string params)
			{
				std::stringstream paramDecode(params);
				std::string param;

				int i = 0;
				while (std::getline(paramDecode, param, '+'))
				{
					switch (i)
					{
					case 0:
						m_position.X = std::stoi(param);
						break;
					case 1:
						m_position.Y = std::stoi(param);
						break;
					}

					i++;
				}
			}

			std::string Player::encodeSave()
			{
				//		xPos+yPos
				return std::to_string(std::round(m_position.X)).append("+").append(std::to_string(std::round(m_position.Y)));
			}

			bool Player::dropHeldItem()
			{
				Items::InventoryItem* item = m_screenInventory->GetHeldItem();
				
				if (item == nullptr) { return false; }

				//FIX, DROPPING WRONG ITEM FOR SOME REASON.
				//Create the object for the item.
				Items::FloorItem* createdItem = new Items::FloorItem(m_position + (m_scale / 2), item->GetType(), 3.5F);
				createdItem->GetPhysics()->AddVelocity(m_textureFlipped ? Vec2{ 1.f, 0.3f } : Vec2{ -1.f, 0.3f });
				createdItem->GetPhysics()->AddRotationalVelocity(std::rand() * 30 / RAND_MAX);
				Renderer::InstantiateObject(Renderer::InstantiateGameObject(createdItem, true, 1, false));

				m_screenInventory->SetItem(m_screenInventory->GetSelectedSlot(), nullptr);
				delete item;


				return true;
			}

			void Player::CreateBloodParticle()
			{
				if (m_particleEmitter->GetParticleCount() == 0)
				{
					//Register blood particles

					auto bParticles = Instantiate::LevelObjectHandler::GetLevelObjects("blood");

					for (auto particleObj : bParticles)
					{
						m_particleEmitter->RegisterParticle(Particles::Particle(particleObj));
					}

					Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_particleEmitter, true, 2, true));
				}

				m_particleEmitter->SetPosition(m_position);
				m_particleEmitter->SpawnParticles(100, { 0.5f, 0.5f }, 0.04f);
			}


			void Player::readKeys()
			{
				m_physics->SetFrictionDrag(Drag);

#if _DEBUG
				if (InputManager::GetKey(PLAYER_DEBUG))
				{
					if (!m_debugKey)
					{
						m_debugKey = true;

						EnterDebug();
					}
				}
				else if (m_debugKey)
				{
					m_debugKey = false;
				}
#endif
				//If the player is pressing the drop item key, drop the item they are holding.
				if (InputManager::GetKeyUpDown(PLAYER_DROP_HELD_ITEM) & InputManager::KEY_STATE::KEY_STATE_PRESSED)
				{
					dropHeldItem();
				}

				bool playerIsSkidding = false;

				//int joyAxesCount;		JOYSTICK INPUT
				//const float* joyAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &joyAxesCount);

				//If the player is frozen, do not check any key presses.
				if (m_frozen <= 0) 
				{
					if (InputManager::GetKey(PLAYER_MOVE_RIGHT))
					{
#if _DEBUG
						if (m_flight)
						{
							m_position += Vec2(InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? 3.0f : 1.4f, 0.f);
							return;
						}
#endif
						if (m_physics->GetVelocity().X < PlayerSpeedCap)
						{
							m_physics->SetFrictionDrag(0);
							m_physics->AddVelocity(Vec2((Time::GameTime::GetScaledDeltaTime() / 0.017f) * (PlayerSpeedCap - m_physics->GetVelocity().X) * (PlayerSpeed), 0.f));

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
						if (m_flight)
						{
							m_position += Vec2(InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? -3.0f : -1.4f, 0.f);
							return;
						}
#endif
						if (m_physics->GetVelocity().X > -PlayerSpeedCap)
						{
							m_physics->SetFrictionDrag(0);
							m_physics->AddVelocity(Vec2((Time::GameTime::GetScaledDeltaTime() / 0.017f) * (PlayerSpeedCap - m_physics->GetVelocity().X) * (-PlayerSpeed), 0.f));
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
				}

				{
					
					//Determines what animation to play currently.
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
				if (m_flight)
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


				//Check if player is jumping and not frozen.
				if (m_frozen <= 0 && InputManager::GetKey(PLAYER_JUMP))
				{
					unsigned char checks = m_physics->GetUpdatesThisFrame();
					while (checks > 0)
					{
						if (m_jumpHeld != 0 && m_jumpHeld < PlayerJumpHoldLength || m_swimming)
						{
							m_jumpHeld++;
							m_physics->AddVelocity(Vec2(0.f, PlayerJumpBonus));
						}
						checks--;
					}

					if (!m_swimming)
					{
						if (m_onGround)
						{
							//Jump Sound

							m_jumpHeld = 1;
							m_onGround = false;
							m_physics->AddVelocity(Vec2(0.f, PlayerJumpHeight + (std::abs(m_physics->GetVelocity().X) * PlayerXSpeedJumpMultiplier)));
						}
					}
					else if (m_jumpHeld != 0)
					{
						m_jumpHeld = 0;
					}


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

				if (player_y_vel > 1.5f)
				{
					m_animator->SetCurrentAnimation(3); //Jumping Animation
					m_begunMotion = true;
					return;
				}
				
				if (player_y_vel < -1.5f)
				{
					m_animator->SetCurrentAnimation(2); //Falling Animation
					m_begunMotion = true;
					return;
				}
			}

		}
	}
}