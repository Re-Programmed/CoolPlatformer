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

#include "../../../Utils/Math/VMath.h"

#include "../../Items/Types/Weapon.h"

#include "../Environment/Effects/BloodMark.h"

#include "../Enemies/Enemy.h"

#include <thread>
#include "../Environment/Effects/Explosion.h"

#define PLAYER_ANIMATION_RUN_WALK_SWITCH 180.f //When the player should switch from the walking to running animation.

#define PLAYER_DAMAGE_ANIMATION_LENGTH 0.75f //How long the damage timer ticks for after the player is attacked.

namespace  GAME_NAME
{
	namespace  Objects
	{
		namespace Player
		{


///Used to define a texture variable in whatever the 
#define TextureDataBase(base)\
				m_textureData.base


#define PLAYER_NO_HEAD_SPRITE TextureDataBase(BagTurnaround) - 1
#define PLAYER_LOOK_BEHIND_SPRITE TextureDataBase(BagTurnaround) + 1
#define PLAYER_LOOK_BAG TextureDataBase(BagTurnaround)
#define PLAYER_FALLEN_SPRITE TextureDataBase(Fall)

#define DefaultPlayerSprite TextureDataBase(DefaultSpites)		//The default sprite to use for the player.

#define PlayerWalkAnim {																																													\
	DefaultPlayerSprite + 1, DefaultPlayerSprite + 2, DefaultPlayerSprite + 3, DefaultPlayerSprite + 2, DefaultPlayerSprite + 1, DefaultPlayerSprite + 4, DefaultPlayerSprite + 5, DefaultPlayerSprite + 4	\
}

#define PlayerRunAnim {																																														\
	DefaultPlayerSprite + 6,DefaultPlayerSprite + 7,DefaultPlayerSprite + 8,DefaultPlayerSprite + 9,DefaultPlayerSprite + 10,DefaultPlayerSprite + 11,DefaultPlayerSprite + 12,DefaultPlayerSprite + 13		\
}

#define PlayerJumpAnim {																																			\
	DefaultPlayerSprite + 14,DefaultPlayerSprite + 15,DefaultPlayerSprite + 16,DefaultPlayerSprite + 17																\
}

#define PlayerFallAnim {																																			\
	DefaultPlayerSprite + 18,DefaultPlayerSprite + 19,DefaultPlayerSprite + 20,DefaultPlayerSprite + 21																\
}

#define PlayerSkidAnim {																																			\
	DefaultPlayerSprite + 22,DefaultPlayerSprite + 23,DefaultPlayerSprite + 24,DefaultPlayerSprite + 25																\
}

#define PlayerFallOverAnim {																															\
	PLAYER_FALLEN_SPRITE + 1, PLAYER_FALLEN_SPRITE + 2, PLAYER_FALLEN_SPRITE + 3, PLAYER_FALLEN_SPRITE													\
}

#define PlayerGetUpAnim {																																\
	PLAYER_FALLEN_SPRITE + 4, PLAYER_FALLEN_SPRITE + 5, PLAYER_FALLEN_SPRITE + 6, PLAYER_FALLEN_SPRITE + 7												\
}

#define PlayerBasicAttackAnim {																																																																						\
	TextureDataBase(BasicAttack), TextureDataBase(BasicAttack) + 1, TextureDataBase(BasicAttack) + 2, TextureDataBase(BasicAttack) + 3, TextureDataBase(BasicAttack) + 4, TextureDataBase(BasicAttack) + 5, TextureDataBase(BasicAttack) + 6, TextureDataBase(BasicAttack) + 7, TextureDataBase(BasicAttack) + 8	\
}

			typedef int8_t PlayerEmotion;
			
			enum PLAYER_EMOTIONS : PlayerEmotion
			{
				ANGRY = SpriteBase(26)
			};

			using namespace Utils;

			const Player::PlayerTextureData Player::TextureData[1] = {
				Player::PlayerTextureData() //Default Sprites (0)
			};

			Player::Player(Vec2 position)
				: ActiveBoxCollisionGravityObject(position, Vec2(DefaultPlayerScaleX, DefaultPlayerScaleY), Rendering::Renderer::GetSprite(DefaultPlayerSprite)), m_screenInventory(new ScreenInventory()),
				m_heldItemLastSprite(nullptr),
				m_playerLight(nullptr),
				m_healthProgressBar(new ProgressBar(
					Vec2(30, 18), Vec2(32, -3), Renderer::GetSprite(SpriteBase(72))->GetSpriteId()
				)),
				m_abilityMeterProgressBar(new ProgressBar(
					Vec2(20, 12), Vec2(46, -3), Renderer::GetSprite(SpriteBase(71))->GetSpriteId()
				)),
				MiscStateGroup("pl"), m_saveState(new PlayerSaveState(this)),
				m_particleEmitter(new Particles::ParticleEmitter(position)),
				m_backpack(new Backpack(0)),		//Create default backpack (load save in constructor).
				m_skillHolder({ 62.f, 7.f }),		//Skill holder (manages update and display of current skill and equipment effects)
				m_textureData(TextureData[0])
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
				Renderer::LoadGUIElement(m_abilityMeterProgressBar, 0);

				//Register animations
				registerAnimations();

				m_physics->SetGravityStrength(DefaultPlayerGravity);

				m_emotionsObject = nullptr;
				//Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_emotionsObject, true, 2, false));

				m_heldItemDisplay = nullptr;

				std::shared_ptr<std::vector<std::string>> states = this->getStates();

				if (states->size() > 0)
				{
					decodeSave(states->at(0));
				}

				assignState(m_saveState);
				
				//TEMP TESTING TODO:REMOVE
				m_skillHolder.UnlockSkill(FLIGHT);
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

				float yOffset = 0;
				//Increment timers for all attributes.
				for (auto playerAttrib : m_currentAttribModifiers)
				{
					playerAttrib.second -= Time::GameTime::GetScaledDeltaTime();
					if (playerAttrib.second < 0)
					{
						m_currentAttribModifiers.erase(playerAttrib.first);
						break;
					}

					/*
						FIX: DO THESE SHOW UP?
						WHAT GIVES YOU ATTRIBUTES. POISON, FOOD, ETC
					*/

					Sprite* attribModSprite = Renderer::GetSprite(4/*Change to show attrib modifier.*/);
					StaticGUIElement* attribModElement = new StaticGUIElement(Vec2{ 112, 12 + yOffset }, Vec2{ 16, 16 }, attribModSprite->GetSpriteId());

					attribModElement->Render();

					delete attribModElement;
					delete attribModSprite;
					yOffset += 20;
				}

				//Check if the player is trying to use a weapon and use it if so.
				if (m_screenInventory->GetHeldItem() != nullptr && InputManager::GetMouseButton(0))
				{
					if (ITEM_DATA[m_screenInventory->GetHeldItem()->GetType()].Actions & WEAPON)
					{
						if (Weapon* w = dynamic_cast<Weapon*>(m_screenInventory->GetHeldItem()))
						{
							w->Use();
							Attack(w->GetDamage(), /*TODO: Give weapons a range attribute*/12.f, 0);
						}
					}

				}

				m_skillHolder.Update();

				//Handle if the player is trying to attack an enemy.
				handleAttack();

				if (m_frozenTimer > 0.f)
				{
					m_frozenTimer -= Utils::Time::GameTime::GetScaledDeltaTime();

					if (m_frozenTimer < 0.f)
					{
						SetFrozen(false);
						//delete m_sprite; NO CAUSES ERROR (DELETING ANIMATION SPRITES)
						m_sprite = Renderer::GetSprite(SpriteBase(0));

						m_rotation = 0.f;
					}
				}

				//Update the current backpack if it is open.
				if (m_backpack->GetIsOpen()) { m_backpack->Render(); }
				else { m_backpack->UpdateCursorItemDisplay(); }

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
				m_healthProgressBar->SetPercentage(static_cast<char>(std::clamp(m_stats.Health, 0.f, 100.f)));

				if (m_playerLight != nullptr)
				{
					m_playerLight->SetPosition(m_position + (m_scale / 2.f));
				}

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


				/*
				Testing, implement something kinda like this but for looking at interesting objects.
				*/
				/*
				if (m_currentPlayerLookDirection == NO_LOOK_DIRECTION || m_currentPlayerLookDirection == FOLLOW_MOUSE)
				{
					if (InputManager::GetMouseButton(1))
					{
						m_currentPlayerLookDirection = FOLLOW_MOUSE;
					}
					else {
						m_currentPlayerLookDirection = NO_LOOK_DIRECTION;
					}
				}
				*/
				updateLookDirection();

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
				m_didRender = true;
#if _DEBUG
				if (m_debug)
				{
					Debug::LevelBuilder::LevelBuilder::Render();
				}
#endif

				Vec4 playerColorVerts[4] = {
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1},
					{1, 1, 1, 1}
				};
				bool playerColorVertsModified = false;

				if (m_damageAnimationTimer > 0.f)
				{
					m_damageAnimationTimer -= Utils::Time::GameTime::GetScaledDeltaTime();
					if (m_damageAnimationTimer < (PLAYER_DAMAGE_ANIMATION_LENGTH / 3.f) || m_damageAnimationTimer > PLAYER_DAMAGE_ANIMATION_LENGTH * (2.f / 3.f))
					{
						for (uint8_t i = 0; i < 4; i++)
						{
							playerColorVerts[i].Y = 0.25f;
							playerColorVerts[i].Z = 0.25f;
						}
						playerColorVertsModified = true;

					}
				}

				

				if (m_swimming)
				{
					const float sin = (std::sinf((float)glfwGetTime()) / 20.f);
					const float sin1 = (std::sinf((float)glfwGetTime() * 1.1f) / 20.f);
					const float sin2 = (std::sinf((float)glfwGetTime() * 1.2f) / 20.f);
					const float sin3 = (std::sinf((float)glfwGetTime() * 1.3f) / 20.f);

					Vec2 vertices[4]{
						Vec2(0.f + sin, 0.f),
						Vec2(0.f + sin1, 1.f),
						Vec2(1.f + sin2, 1.f),
						Vec2(1.f + sin3, 0.f)
					};
					
					DynamicSprite d(m_sprite->GetSpriteId(), vertices);
					d.UpdateTextureColor(playerColorVerts);
					d.Render(cameraPosition, m_position + m_scale, m_scale, m_rotation + 180.f);
					return;
				}
				else {
					if (m_sprite != nullptr)
					{
						//Check if the player's color should update.
						if (playerColorVertsModified)
						{
							DynamicSprite* coloredSprite = new DynamicSprite(m_sprite->GetSpriteId());
							coloredSprite->UpdateTextureColor(playerColorVerts);
							coloredSprite->Render(cameraPosition, m_position + m_scale + (m_textureFlipped ? (m_scale * Vec2::MinusOneX) : 0), m_scale * (m_textureFlipped ? Vec2::MinusOneXOneY : 1), m_rotation + 180.f);
							delete coloredSprite;
						}
						else {
							//DEFAULT RENDER MODE.

							m_sprite->Render(cameraPosition, m_position + (m_textureFlipped ? (m_scale * Vec2::OneX) : 0), m_scale * (m_textureFlipped ? Vec2::MinusOneXOneY : 1), m_rotation);
						}
					}
					//Render emotions object if it should be rendered.
					if (m_emotionsObject != nullptr)
					{
						m_emotionsObject->Render(cameraPosition);
					}
				}

				/*
					Held item rendering.
				*/

				if (m_heldItemDisplay != nullptr && m_heldItemDisplay->GetScale().X > 8)
				{
					
					const int&& baseSpriteId = Items::ITEM_DATA[m_screenInventory->GetHeldItem()->GetType()].HeldTexture;

					//If the player is currently attacking, the item will be rendered outward from their body.
					if (m_animator->GetCurrentAnimationIndex() == 7 /*Basic Attack Anim*/)
					{
						const int frame = 0;
						m_heldItemLastSprite = Renderer::GetSprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						//Offset position is determined by what frame of attack the player is on.
						Vec2 offsetPosition = Vec2::Zero;
						switch (m_animator->GetCurrentAnimation()->GetFrame())
						{
						case 0:
							offsetPosition = { -6.25f, 3.f };
							break;
						case 1:
							offsetPosition = { -5.33f, 2.f };
							break;
						case 2:
							offsetPosition = { -5.f, 1.f };
							break;
						case 3:
							offsetPosition = { -4.75f, 0.f };
							break;
						case 4:
							offsetPosition = { -5.f, -1.f };
							break;
						case 5:
							offsetPosition = { -5.33f, -2.f };
							break;
						case 6:
							offsetPosition = { -6.25f, -3.f };
							break;
						default:
							offsetPosition = { -6.25f, -4.f };
							break;
						}

						if (m_textureFlipped)
						{
							
							m_heldItemDisplay->GetSprite()->Render(cameraPosition, offsetPosition + m_position + Vec2{ 16.f + m_heldItemDisplay->GetScale().X - 7, 0 }, m_heldItemDisplay->GetScale() * Vec2 { -1, 1 }, 0.0F);
						}
						else {
							m_heldItemDisplay->GetSprite()->Render(cameraPosition, m_position + Vec2{ 0.f, 0.f }, m_heldItemDisplay->GetScale(), 0.0F);
						}
						return;
					}

					const float playerYVel = m_physics->GetVelocity().Y + m_physics->GetGravitationalVelocity();
					if (playerYVel > 1.5f && !m_onGround)
					{
						const int frame = 0;
						m_heldItemLastSprite = Renderer::GetSprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						m_heldItemDisplay->SetPosition(m_position + (m_textureFlipped ? Vec2(6.75f, -0.5f) : Vec2(0, -0.5f)));
					}else if (playerYVel < -1.5f && !m_onGround)
					{
						const int frame = 2;
						m_heldItemLastSprite = Renderer::GetSprite(baseSpriteId + frame);
						m_heldItemDisplayFrameOffset = frame;
						m_heldItemDisplay->SetSprite(m_heldItemLastSprite);

						m_heldItemDisplay->SetPosition(m_position + (m_textureFlipped ? Vec2(2.6f, 7.f) : Vec2(4.5f, 7.f)));
					}
					else if (m_physics->GetVelocity().X > 0.3 || m_physics->GetVelocity().X < -0.3)
					{
						int&& frame = m_animator->GetCurrentAnimation()->GetFrame();

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

						delete m_heldItemLastSprite; //?? memory?
						m_heldItemLastSprite = Renderer::GetSprite(baseSpriteId + frame);
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

			void Player::Damage(float damage, GameObject* cause)
			{
				float maxHealth = 100.f + m_skillHolder.GetEquipmentBoostEffect("Health", m_backpack);

				if(damage > 0.f){ CreateBloodParticle(cause); }

				m_stats.Health -= damage;
				m_healthProgressBar->SetPercentage(static_cast<char>(std::clamp(100.f * m_stats.Health / maxHealth, 0.f, maxHealth)));

				m_damageAnimationTimer = PLAYER_DAMAGE_ANIMATION_LENGTH;

				if (m_stats.Health <= 0)
				{
					Kill();
				}
			}

			void Player::Heal(float amount)
			{
				float maxHealth = 100.f + m_skillHolder.GetEquipmentBoostEffect("Health", m_backpack);

				m_stats.Health += maxHealth;

				if (m_stats.Health > maxHealth)
				{
					m_stats.Health = maxHealth;
				}

				m_healthProgressBar->SetPercentage(static_cast<char>(std::clamp(100.f * m_stats.Health / maxHealth, 0.f, maxHealth)));

			}

			void Player::Kill()
			{

			}

#define GetObjectW GetObject //Stupid windows define thing that needs fixed.

			void Player::Attack(float damage, float range, int atkAnimation)
			{
				for (ActiveCollider* ac : CollisionManager::GetActiveColliders())
				{
					if (Enemies::Enemy* enemy = dynamic_cast<Enemies::Enemy*>(ac->GetObject()))
					{
						if (Vec2::Distance(enemy->GetPosition() + (enemy->GetScale() / 2.f), this->m_position + (range / 2.f)) <= range)
						{
							
						}
					}
				}
			}

			void Player::SetPlayerTextureData(TEXTURE_OFFSETS offsets)
			{
				m_textureData = TextureData[offsets];
				registerAnimations();
			}

			void Player::ApplyAttributeModifier(ATTRIBUTE_MODIFIER attrib, float seconds)
			{
				m_currentAttribModifiers.emplace(std::make_pair(attrib, seconds));
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

					m_heldItemDisplay->SetSprite(Renderer::GetSprite(customHeldTexture));
					return;
				}

				m_heldItemDisplay->SetSprite(Items::ITEMTYPE_GetItemTypeTexture(item->GetType()));

				//TODO: ITEM RANDOMLY CHANGES TO OTHER SPRITES WHEN THE PLAYER SWITCHES ITEMS WHILE RUNNING.
				m_heldItemDisplayFrameOffset = 0;
			}

#define COLLISION_VEL_STOP_DAMPING 0.1f

			void Player::AddVelocity(Vec2 velocity)
			{
				m_physics->AddVelocity(velocity);
			}

			void Player::onCollision(Vec2 push, GameObject* collided)
			{
				if (m_swimming) { return; }
				if (m_foundCollisionInTick) { return; }
				if (push.Y > 0)
				{
					if (m_isFlying)
					{
						//Reset flying graivty.
						m_isFlying = false;
						m_physics->SetGravityStrength(DefaultPlayerGravity);
					}

					m_onGround = true;
					m_foundCollisionInTick = true;
					m_physics->SetVelocityY(0.f);

					//Calculate fall damage.
					if (m_airTime > 1.85f)
					{
						std::cout << m_airTime << std::endl;

						Damage(((float)m_airTime - 1.85f) * 10.f, collided);
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
						m_position.X = std::stof(param);
						break;
					case 1:
						m_position.Y = std::stof(param);
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
				createdItem->GetPhysics()->AddRotationalVelocity(std::rand() * 30.f / RAND_MAX);
				Renderer::InstantiateObject(Renderer::InstantiateGameObject(createdItem, true, 1, false));

				m_screenInventory->SetItem(m_screenInventory->GetSelectedSlot() - 1, nullptr);

				/*********************
					TODO: without this line, wouldn't it cause a memory leak?
					Without the line, dropping tools actually works tho...
				**********************/
				delete item;


				return true;
			}

			void Player::registerAnimations()
			{
#define RegisterAnimation(data_name, data_source, data_out, spf) AnimData data_name; \
				for(int i : data_source){ data_name.Sprites.push_back(Renderer::GetSprite(i)); }; \
				std::shared_ptr<GAME_NAME::Components::Animation::Animation> data_out(new GAME_NAME::Components::Animation::Animation(data_name, spf)); 

#pragma region Init Animation

				RegisterAnimation(walk_data, PlayerWalkAnim, walk_anim, ANIM_12_SPF);						  //0
				RegisterAnimation(run_data, PlayerRunAnim, run_anim, ANIM_16_SPF);							  //1
				RegisterAnimation(fall_data, PlayerFallAnim, fall_anim, ANIM_12_SPF);						  //2
				RegisterAnimation(jump_data, PlayerJumpAnim, jump_anim, ANIM_12_SPF);						  //3
				RegisterAnimation(skid_data, PlayerSkidAnim, skid_anim, ANIM_12_SPF);						  //4 
				RegisterAnimation(fall_over_data, PlayerFallOverAnim, fall_over_anim, ANIM_6_SPF);			  //5
				RegisterAnimation(get_up_data, PlayerGetUpAnim, get_up_anim, ANIM_6_SPF);					  //6
				RegisterAnimation(basic_attack_data, PlayerBasicAttackAnim, basic_attack_anim, ANIM_16_SPF);  //7

#pragma endregion

				std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ walk_anim, run_anim, fall_anim, jump_anim, skid_anim, fall_over_anim, get_up_anim, basic_attack_anim };

				m_animator = new AnimatorComponent(anims);
			}

			void Player::CreateBloodParticle(GameObject* cause)
			{
				if (m_particleEmitter->GetParticleCount() == 0)
				{
					//Register blood particles

					auto bParticles = Instantiate::LevelObjectHandler::GetLevelObjects("blood");

					for (auto particleObj : bParticles)
					{
						Particles::Particle bloodParticle = Particles::Particle(particleObj);

						bloodParticle.TargetOpacity = 0;
						
						m_particleEmitter->RegisterParticle(bloodParticle);
					}


					Renderer::InstantiateObject(Renderer::InstantiateGameObject(m_particleEmitter, true, 2, true));
				}

				m_particleEmitter->SetPosition(m_position + m_scale/2);
				m_particleEmitter->SetAllowCollisions(true);
				

				//Create blood on floor if the player fell.
				if (cause == nullptr)
				{
					m_particleEmitter->SetForcedSpawnVelocity(0);
					m_particleEmitter->SpawnParticles(75, { 0.5f, 0.5f }, 0.04f);
					return;
				}

				if (instanceof<Environment::Effects::Explosion>(cause))
				{
					Environment::BloodMark* floorMark = new Environment::BloodMark(this, m_position + Vec2(m_scale.X / 2.f, 0.f));
					Renderer::LoadObject(floorMark, 1);
					m_particleEmitter->SetForcedSpawnVelocity(Vec2{ ((m_position.X + m_scale.X/2) - cause->GetPosition().X) / 5.f , ((m_position.Y + m_scale.Y/2) - cause->GetPosition().Y) / 5.f});
					m_particleEmitter->SpawnParticles(75, { 0.5f, 0.5f }, 0.04f);
					return;
				}



				//ONLY CONTINUE TO HERE IF THE CAUSE OF DAMAGE WAS FALLING.

				//Freeze player after falling from a great height.
				SetFrozen(true, FALLEN);
				m_frozenTimer = 5.f;

				Environment::BloodMark* floorMark = new Environment::BloodMark(cause, m_position + Vec2(m_scale.X / 2.f, 0.f));
				Renderer::LoadObject(floorMark, 1);
				//Renderer::InstantiateObject(Renderer::InstantiateGameObject(floorMark, false, 2, false));
			}


			void Player::readKeys()
			{
				//Jump to stop sitting on a bench.
				if (m_currentPlayerLookDirection == SITTING_FORWARD)
				{
					if (InputManager::GetKey(PLAYER_JUMP))
					{
						SetFrozen(false);
					}
				}

				m_physics->SetFrictionDrag(Drag);

				//TESTING: REMOVE
				//Fake damage by pressing TAB
				if ((InputManager::GetKeyUpDown(DEBUG_OBJECT_MENU) & InputManager::KEY_STATE::KEY_STATE_PRESSED) && !m_debug)
				{
					Damage(10, nullptr);
				}

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

				//Check if the player is pressing the key to toggle their flashlight.
				if (InputManager::GetKeyUpDown(PLAYER_TOGGLE_FLASHLIGHT) & InputManager::KEY_STATE::KEY_STATE_PRESSED)
				{
					togglePlayerLight();
				}

				//If the player is pressing the drop item key, drop the item they are holding.
				if (InputManager::GetKeyUpDown(PLAYER_DROP_HELD_ITEM) & InputManager::KEY_STATE::KEY_STATE_PRESSED)
				{
					dropHeldItem();
				}

				/*
					Player backpack opening.
				*/
				if (InputManager::GetKeyUpDown(PLAYER_OPEN_BACKPACK) & InputManager::KEY_STATE_PRESSED)
				{

					if (m_backpack->GetIsOpen())
					{
						//Close backpack.
						m_backpack->Close();

						//Update held item in case the player changed their current selected item.
						m_screenInventory->SelectSlot(m_screenInventory->GetSelectedSlot());

						SetFrozen(false);
						return;
					}

					//Is the player able to open their bag?
					if (!m_onGround || m_frozen) { return; }

					//Open backpack GUI.
					m_backpack->Open();

					//Freeze player inputs and use bag sprite.
					SetFrozen(true, BAG);
					return;
				}


				bool playerIsSkidding = false;


				//int joyAxesCount;		JOYSTICK INPUT
				//const float* joyAxes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &joyAxesCount);


				//If the player is frozen, do not check any key presses.
				if (m_frozen <= 0) 
				{
					float addSpeedCap = 0.f;

					//Check for speed modifier.
					if (m_currentAttribModifiers.contains(ATTRIBUTE_MODIFIER::SPEED_UP))
					{
						addSpeedCap += PlayerSpeedCap / 2.f;
					}
	
					if (InputManager::GetKey(PLAYER_MOVE_RIGHT))
					{

#if _DEBUG
						if (m_flight)
						{
							m_position += Vec2(InputManager::GetKey(PLAYER_DEBUG_ADD_SPEED) ? 3.0f : 1.4f, 0.f);
							return;
						}
#endif
						if (m_physics->GetVelocity().X < PlayerSpeedCap + addSpeedCap)
						{
							m_physics->SetFrictionDrag(0.f);
							m_physics->AddVelocity(Vec2(((float)Time::GameTime::GetScaledDeltaTime() / 0.017f) * (PlayerSpeedCap - m_physics->GetVelocity().X) * (PlayerSpeed), 0.f));

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
						if (m_physics->GetVelocity().X > -PlayerSpeedCap - addSpeedCap)
						{
							m_physics->SetFrictionDrag(0);
							m_physics->AddVelocity(Vec2(((float)Time::GameTime::GetScaledDeltaTime() / 0.017f) * (PlayerSpeedCap - m_physics->GetVelocity().X) * (-(PlayerSpeed - 0.0165F)), 0.f));
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
				
				//If the player is not attacking, calculate animations.
				if(m_attackCooldown <= 0)
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
				
				/*
					-----
					CHECK PLAYER ABILITIES AND ACTIONS.
					-----
				*/
				if (m_skillHolder.CanUseAbility(FLIGHT))
				{
					if (m_stats.AbilityMeter >= 10.f)
					{
						//FLIGHT (GLIDING) ABILITY, DISABLE IF PLAYER IS MISSING CERTAIN ITEMS.
						if (InputManager::GetKeyUpDown(PLAYER_JUMP) & InputManager::KEY_STATE_PRESSED)
						{
							if (!m_swimming && !m_isFlying && m_frozen <= 0 && m_jumpHeld != 1 && m_airTime > 0.4f /*Make sure player has to start gliding at the peak of their jump.*/)
							{
								//DEBUGGING
								std::cout << "FLIGHT ENABLED" << std::endl;

								//Subtract from ability meter based on cost of ability.
								updateAbilityMeter(-10.f);

								//Set flying, "double jump" occured.
								m_isFlying = true;
								m_physics->SetVelocityY(200.f);
								m_physics->SetGravityStrength(DefaultPlayerGravity - FlyingGravityReduction - 0.5f);
							}
						}
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
						m_animator->SetSpeedMult((double)anim_momentum / 100.0);
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


				m_animator->SetSpeedMult(1.0);
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

			void Player::updateLookDirection()
			{
				//Player is currently in an attacking animation, do not interrupt.
				if (m_animator->GetCurrentAnimationIndex() == 7) { return; }

				if (m_currentPlayerLookDirection == FOLLOW_MOUSE)
				{
					delete m_sprite;
					m_sprite = Renderer::GetSprite(PLAYER_NO_HEAD_SPRITE);

					if (m_emotionsObject == nullptr)
					{
						m_emotionsObject = new ChildGameObject(Vec2(DefaultPlayerScaleX, 12.25), Vec2(-DefaultPlayerScaleX, DefaultPlayerScaleY * 0.519230769f), Renderer::GetSprite(PLAYER_EMOTIONS::ANGRY), this);
					}
					else {
						m_emotionsObject->Update(TestGame::FirstWindow);
					}
				}
				else {
					if (m_emotionsObject != nullptr)
					{
						delete m_emotionsObject;
						m_emotionsObject = nullptr;
					}
				}

				switch (m_currentPlayerLookDirection)
				{
					case FOLLOW_MOUSE:
					{
						/*
							TODO: FIX THIS SO THE HEAD LOOKS BETTER.
						*/


						//Get what angle the head must rotate to point at the mouse.
						Vec2 mouseDistance = InputManager::GetMouseWorldPosition(TestGame::INSTANCE->GetCamera()) - m_emotionsObject->GetPosition();
						float rotation = -MathUtils::to_degf(std::atanf(mouseDistance.Y / mouseDistance.X));
						m_emotionsObject->SetRotationAboutCenter(rotation);
						break;
					}

					case BEHIND:
					{
						//delete m_sprite;
						m_sprite = Renderer::GetSprite(PLAYER_LOOK_BEHIND_SPRITE);
						break;
					}

					case FALLEN:
					{
						if (m_frozenTimer < 0.f) { break; }

						if (m_frozenTimer < ANIM_6_SPF * 4.f)
						{
							if (m_animator->GetCurrentAnimation() == nullptr)
							{
								break;
							}

							//Reset falling animation via incrementing frame.
							m_animator->GetCurrentAnimation()->IncrementFrame(nullptr);
							m_animator->SetCurrentAnimation(6); //Get Up Anim
							m_animator->SetSpeedMult(1.f);

							m_rotation = 0.f;

							if (m_animator->GetCurrentAnimation()->GetFrame() == 3)
							{
								//Reset animation via incrementing frame.
								m_animator->GetCurrentAnimation()->IncrementFrame(nullptr);
								m_animator->SetCurrentAnimation(-1); //No Animation
								m_animator->SetSpeedMult(0.f);
							}

							break;
						}

						m_animator->SetCurrentAnimation(5); //Fall Over Anim
						

						//Update scale to keep sprites relative size the same.
						if (m_animator->GetCurrentAnimation()->GetFrame() > 0)
						{
							m_scale = Vec2(26, 26);
						}

						//Animation done.
						if (m_animator->GetCurrentAnimation()->GetFrame() == 3)
						{
							m_animator->SetSpeedMult(0.f);

							//delete m_sprite;
							m_sprite = Renderer::GetSprite(PLAYER_FALLEN_SPRITE);
							m_rotation = -11.f;

						}
						else {
							m_animator->SetSpeedMult(1.f);
						}

						break;
					}

					case BAG:
					{
						//delete m_sprite;
						m_sprite = Renderer::GetSprite(PLAYER_LOOK_BAG);
						break;
					}

					case SITTING_FORWARD:
					{
						//TODO: Animate sitting down.

						m_physics->SetVelocity(0);

						break;
					}

					default:
					{
						m_scale = Vec2(16, 26);
						return;
					}
				}
			}

			void Player::updateAbilityMeter(float amount)
			{
				m_stats.AbilityMeter += amount;
				m_abilityMeterProgressBar->SetPercentage(static_cast<char>(std::clamp(m_stats.AbilityMeter, 0.f, 100.f)));
			}

			void Player::togglePlayerLight()
			{
using namespace Lighting;

				if (m_playerLight == nullptr)
				{
					m_playerLight = new LightingSource(m_position, 45.f, 5.f, POINT_LIGHT, true, true);
				}
				else
				{
					m_playerLight->Off(true);
					delete m_playerLight;
					m_playerLight = nullptr;
				}
			}

			void Player::handleAttack()
			{

				if (m_attackCooldown > 0)
				{
					m_attackCooldown -= Utils::Time::GameTime::GetScaledDeltaTime();

					if (m_attackCooldown <= 0)
					{
						//Completed attack.

						if (!m_textureFlipped)
						{
							//Offset position to adjust for offset visual position in attack animation.
							m_position += Vec2(13.f, 0);
						}

						m_frozen = false;
						m_animator->SetCurrentAnimation(-1);
						m_sprite = Renderer::GetSprite(DefaultPlayerSprite);
					}

					return;
				}

				//Player is trying to attack.
				if (InputManager::GetMouseButton(1))
				{
					if (m_frozen) { return; }
					Vec2 mousePos = InputManager::GetMouseWorldPosition(TestGame::INSTANCE->GetCamera());

					if (mousePos.X < m_position.X)
					{
						//Offset position to adjust for offset visual position in attack animation.
						m_position -= Vec2(13.f, 0);
						m_textureFlipped = false;
						
						m_physics->AddVelocity({6.5f, 0.f});
					}
					else
					{
						m_textureFlipped = true;
					}

					//Play attacking animation.
					//m_physics->SetVelocityX(0.f);
					m_animator->SetCurrentAnimation(7, this);
					m_animator->SetSpeedMult(2.f);
					m_scale = { 26.f, 26.f }; //Adjust scale to that of the animation sprites.
					m_frozen = true;
					m_attackCooldown = (8.0 * 0.5) * (double)ANIM_16_SPF; //(frames * 1/speed * seconds_per_frame)


					const Vec2 damageOrigin = m_position + Vec2{ (m_textureFlipped ? 12.f : -12.f), 0.f };

					int AOE = 20, damage = 2;

					if (GetInventory()->GetHeldItem())
					{

						const ItemData& heldItemData = ITEMTYPE_GetItemData(this->GetInventory()->GetHeldItem()->GetType());
						if (heldItemData.Actions & WEAPON)
						{
							const std::string& attribute = heldItemData.Attributes.at(TOOL_ACTION::WEAPON);
							damage = std::stoi(attribute.substr(0, attribute.find_first_of(',')));
							AOE = std::stoi(attribute.substr(attribute.find_last_of(',') + 1));
						}
					}

					//Handle damage.
					for (Enemies::Enemy* enemy : Enemies::Enemy::EnemyRegistry)
					{
						if (Vec2::Distance(enemy->GetPosition() + (enemy->GetScale()/2.f), damageOrigin) < AOE)
						{
							enemy->Damage(damage, m_position + (m_scale/2.f));
						}
					}
				}
			}


		}
	}
}