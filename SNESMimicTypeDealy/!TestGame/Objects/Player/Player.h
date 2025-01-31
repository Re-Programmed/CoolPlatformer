#pragma once
#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../../../Utils/Math/Vec2.h"
#include "../../../Rendering/Renderers/Renderer.h"
#include "../../../Components/Animation/AnimatorComponent.h"
#include "../../../Audio/SoundManager.h"
#include "../../../Components/ChildGameObject.h"
#include "../../../Objects/Particles/ParticleEmitter.h"
#include "../../../Objects/GUI/Progress/ProgressBar.h"

#include "ScreenInventory.h"
#include "Backpack/Backpack.h"
#include "Skills/SkillHolder.h"

#include "../../../Rendering/Lighting/LightingSource.h"


#ifndef _PLAYERDEF
#define _PLAYERDEF


constexpr float DefaultPlayerScaleX = 16.f;	//The default size for the player.
constexpr float DefaultPlayerScaleY = 26.f;	//The default size for the player.

constexpr int DefaultPlayerSprite = GLOBAL_SPRITE_BASE;		//The default sprite to use for the player.
constexpr int PlayerWalkAnim[8] = {
	SpriteBase(1), SpriteBase(2), SpriteBase(3), SpriteBase(2), SpriteBase(1), SpriteBase(4), SpriteBase(5), SpriteBase(4)
};
constexpr int PlayerRunAnim[8] = {
	SpriteBase(6),SpriteBase(7),SpriteBase(8),SpriteBase(9),SpriteBase(10),SpriteBase(11),SpriteBase(12),SpriteBase(13)
};

constexpr int PlayerJumpAnim[4] = {
	SpriteBase(14),SpriteBase(15),SpriteBase(16),SpriteBase(17)
};
constexpr int PlayerFallAnim[4] = {
	SpriteBase(18),SpriteBase(19),SpriteBase(20),SpriteBase(21)
};
constexpr int PlayerSkidAnim[4] = {
	SpriteBase(22),SpriteBase(23),SpriteBase(24),SpriteBase(25)
};

constexpr float PlayerSpeed = .04f;			//The amount of velocity to add for each frame the player is moving.
constexpr float PlayerSpeedCap = 200.f;		//The maximum amount of velocity the player can accelerate at (ignoring gravity).

constexpr float PlayerJumpHeight = 60.f;	//The vertical velocity applied on the inital press of jump.
constexpr float PlayerJumpBonus = 13.f;		//How vertical velocity to add for every frame the jump button is held after the inital jump.
constexpr int8_t PlayerJumpHoldLength = 10;	//The maximum amount of frames the player can hold jump for.
constexpr float PlayerXSpeedJumpMultiplier = 0.08f; //The multiplier for how much of the X speed is added to the players jump.

constexpr float DefaultPlayerGravity = 5.5f;	//The default gravity.
constexpr float SwimmingPlayerGravity = 0.4f;	//The default gravity while underwater.

constexpr float FlyingGravityReduction = 4.f;   //How much gravity will be reduced by when gliding.

constexpr float Drag = 4.f;					//How much the player should slow down each frame when they stop moving.

namespace  GAME_NAME
{
	namespace  Objects
	{
		namespace Player
		{
			using namespace Components;
			using namespace Physics;
			using namespace Collision;
			using namespace Animation;
			using namespace GUI;

			/// <summary>
			/// Possible effects that can be added to the player from eating food or other events.
			/// </summary>
			enum ATTRIBUTE_MODIFIER
			{
				SPEED_UP,
				JUMP_BOOST
			};

			class Player	//The class used for the player GameObject.
				: public ActiveBoxCollisionGravityObject, public MiscStateGroup
			{
			public:
				Player(Vec2 position);
				~Player();

				void Update(GLFWwindow* window);

				void SetSwimming(bool swimming);		//Enables low gravity and swimming mode. (Sets m_swimming to true)

				void Render(const Vec2& cameraPosition) override;	

#if _DEBUG
				inline bool GetDebug() { return m_debug; }

				void EnterDebug();
				void ToggleFlight();
#endif

				/// <summary>
				/// Damage the player the specified amount with the given object as the cause. If this was fall damage, the ground will recieve a splatter (Otherwise cause should be nullptr).
				/// </summary>
				/// <param name="damage"></param>
				/// <param name="cause"></param>
				void Damage(float damage, GameObject* cause);

				/// <summary>
				/// Heal the player and ensure that the players health doesn't exceed the maximum with armour effects applied.
				/// </summary>
				/// <param name="health"></param>
				void Heal(float health);
				void Kill();

				/// <summary>
				/// Uses the specified damage and range to play an attacking animation and create a damage hitbox.
				/// </summary>
				void Attack(float damage, float range, int atkAnimation = 0);

				/// <summary>
				/// Spawns random blood particles around the player. (can be used to imitate damage, is also called when Damage() is called)
				/// </summary>
				void CreateBloodParticle(GameObject* cause);

				/// <summary>
				/// Apply some modifier to the player for some amount of time.
				/// </summary>
				/// <param name="attrib"></param>
				void ApplyAttributeModifier(ATTRIBUTE_MODIFIER attrib, float seconds);

				void SetHeldItem(Items::InventoryItem* item);
				inline void RemoveHeldItem()
				{
					if (m_heldItemDisplay != nullptr)
					{
						m_heldItemDisplay->SetScale(Vec2(0));
					}
				}

				inline ScreenInventory* GetInventory()
				{
					return m_screenInventory;
				}

				enum PLAYER_LOOK_DIRECTION
				{
					NO_LOOK_DIRECTION,
					BEHIND,
					AT_POINT,
					FOLLOW_MOUSE,
					BAG,
					FALLEN,
					SITTING_FORWARD
				};

				/// <summary>
				/// Sets an object to freeze the player.
				/// </summary>
				/// <param name="frozen">Freeze the player?</param>
				inline void SetFrozen(bool frozen, PLAYER_LOOK_DIRECTION direction = NO_LOOK_DIRECTION, Vec2 point = Vec2::Zero)
				{
					m_frozen += frozen ? 1 : -1;
					SetLookDirection(direction, point);
				}

				inline Backpack* const GetBackpack()
				{
					return m_backpack;
				}
				
				inline void SetLookDirection(PLAYER_LOOK_DIRECTION direction, Vec2 point = Vec2::Zero)
				{
					m_currentPlayerLookDirection = direction;
					m_playerLookPoint = point;
				}

				void AddVelocity(Vec2 velocity);

			protected:
				void onCollision (Vec2 push, GameObject* gameObject) override;	//Called when a collision occurs.
				void beforeCollision() override;		//Called before any collisions are calculated to allow for resetting the jump conditions.

			private:

				std::unordered_map<ATTRIBUTE_MODIFIER, float> m_currentAttribModifiers;

				/// <summary>
				/// Used to turn the player red for some period of time when they are damaged.
				/// </summary>
				float m_damageAnimationTimer = 0.f;

				Lighting::LightingSource* m_playerLight;

				/// <summary>
				/// If using AT_POINT for player look direction, where to look.
				/// </summary>
				Vec2 m_playerLookPoint = Vec2::Zero;
				/// <summary>
				/// The current player look state.
				/// </summary>
				PLAYER_LOOK_DIRECTION m_currentPlayerLookDirection = NO_LOOK_DIRECTION;

				/// <summary>
				/// The players current skill data.
				/// </summary>
				SkillHolder m_skillHolder;

				/// <summary>
				/// Decodes the given string as player save data.
				/// </summary>
				/// <param name="params"></param>
				void decodeSave(const std::string params);
				/// <summary>
				/// Returns the encoded version of the player save data.
				/// </summary>
				/// <returns></returns>
				std::string encodeSave();

				/// <summary>
				/// Misc state for player save data.
				/// </summary>
				class PlayerSaveState
					: public MiscState
				{
				public:
					PlayerSaveState(Player* player)
						: m_player(player)
					{
						
					}

					MiscState::SaveParam Encode() override final
					{
						return m_player->encodeSave();
					}

					void Decode(const MiscState::SaveParam param) override final
					{
						m_player->decodeSave(param);
					}

				private:
					Player* const m_player;
				};

				PlayerSaveState* const m_saveState;			//Stores all data for the players current save state.

				/// <summary>
				/// The players current backpack that can be used to store items and equip gear.
				/// </summary>
				Backpack* m_backpack;

				/// <summary>
				/// Drops the currently held item and returns true if the item was sucussfully dropped.
				/// </summary>
				/// <returns></returns>
				bool dropHeldItem();

				/// <summary>
				/// If the player is frozen they cannot move but can still be affected by gravity or other objects.
				/// The value of frozen can go above 1, that way if multiple objects are currently freezing the player, the player will remain frozen until all objects have stopped freezing the player.
				/// </summary>
				int8_t m_frozen = 0;


				/// <summary>
				/// If set to some value, will tick down each frame until 0 and then will unfreeze player.
				/// </summary>
				float m_frozenTimer = -1.f;

				GameObject* m_heldItemDisplay;				//Follows the player to display the current held item.
				int m_heldItemDisplayFrameOffset = 0;		//How many sprite difference from the default held item sprite to its current animation frame.
				Sprite* m_heldItemLastSprite;

				ScreenInventory* const m_screenInventory;	//Player's three main inventory slots.

				/// <summary>
				/// Represents data about the players stamina, health, etc.
				/// </summary>
				struct {
					float Health = 100.f;
					float AbilityMeter = 100.f;
				} m_stats;

				ProgressBar* m_healthProgressBar;		//Progress bar for displaying health.
				ProgressBar* m_abilityMeterProgressBar;	//Progress bar for ability meter.

				Particles::ParticleEmitter* const m_particleEmitter;

				bool m_onGround = false;				//If the player is on the ground.
				bool m_foundCollisionInTick = false;	//Used for checking when the player leaves the ground.
				bool m_swimming = false;				//If the player is swimming.
				int m_jumpHeld = 0;						//Used for determining how many frames the jump button has been held after the player jumps.
				bool m_begunMotion = false;				//Used for animation checks.

				double m_airTime = 0;					//Time the player has spent in the air. (Used to calculate fall damage)

				bool m_isFlying = false;				//True if the player is currently flying.

				AnimatorComponent* m_animator;			//Animator for walking, jumping, etc.
				Components::ChildGameObject* m_emotionsObject;	//Object overlayed on the player for expressions, etc.

				void readKeys();						//Called to determine what buttons are pressed and apply velocity based on those buttons.
				void setAnimations(bool playerIsSkidding, float& anim_momentum);	//Called to determine what animation the player should be playing.
				void updateLookDirection();				//Used to update player look state.

#if _DEBUG
				bool m_debug = false, m_debugKey = false, m_flight = false;
#endif
				
				inline void enableUnderwaterMusic() const	//Pauses the current level music and starts the underwater music in the same position.
				{
					Audio::AudioPlayer* player = Audio::SoundManager::GetAudioPlayer();

					Audio::TimeSeconds ts = player->getStreamTime(Audio::SoundManager::BGMusic);
					player->setPause(Audio::SoundManager::BGMusic, true);

					player->seek(Audio::SoundManager::WaterMusic, ts);
					player->setPause(Audio::SoundManager::WaterMusic, false);
				}

				inline void disableUnderwaterMusic() const	//Pauses the underwater music and starts the current level music in the same position.
				{
					Audio::AudioPlayer* player = Audio::SoundManager::GetAudioPlayer();

					Audio::TimeSeconds ts = player->getStreamTime(Audio::SoundManager::WaterMusic);
					player->setPause(Audio::SoundManager::WaterMusic, true);

					player->seek(Audio::SoundManager::BGMusic, ts);
					player->setPause(Audio::SoundManager::BGMusic, false);
				}

				/// <summary>
				/// Updates the ability meter stat and corrseponding graphics.
				/// </summary>
				/// <param name="amount">[float] - How much to add to the ability meter.</param>
				void updateAbilityMeter(float amount);

				void togglePlayerLight();

				/// <summary>
				/// Counts down between attacks to prevent spamming one attack.
				/// </summary>
				double m_attackCooldown;
				void handleAttack();
			};

		};
	};
};

#endif