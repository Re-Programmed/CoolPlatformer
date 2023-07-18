#pragma once
#include "../../../Components/Physics/Collision/Helpers/ActiveBoxCollisionGravityObject.h"
#include "../../../Utils/Math/Vec2.h"
#include "../../../Rendering/Renderers/Renderer.h"
#include "../../../Components/Animation/AnimatorComponent.h"
#include "../../../Audio/SoundManager.h"

#ifndef _PLAYERDEF
#define _PLAYERDEF

constexpr float DefaultPlayerScaleX = 17.f;	//The default size for the player.
constexpr float DefaultPlayerScaleY = 17.f;	//The default size for the player.

constexpr int DefaultPlayerSprite = 1;		//The default sprite to use for the player.

constexpr float PlayerSpeed = .04f;			//The amount of velocity to add for each frame the player is moving.
constexpr float PlayerSpeedCap = 200.f;		//The maximum amount of velocity the player can accelerate at (ignoring gravity).

constexpr float PlayerJumpHeight = 60.f;	//The vertical velocity applied on the inital press of jump.
constexpr float PlayerJumpBonus = 13.f;		//How vertical velocity to add for every frame the jump button is held after the inital jump.
constexpr int8_t PlayerJumpHoldLength = 10;	//The maximum amount of frames the player can hold jump for.

constexpr float DefaultPlayerGravity = 4.5f;	//The default gravity.
constexpr float SwimmingPlayerGravity = 0.4f;	//The default gravity while underwater.

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

			class Player	//The class used for the player GameObject.
				: public ActiveBoxCollisionGravityObject
			{
			public:
				Player(Vec2 position);
				~Player();

				void Update(GLFWwindow* window);

				void SetSwimming(bool swimming);		//Enables low gravity and swimming mode. (Sets m_swimming to true)

				void Render(const Vec2 cameraPosition);	
			protected:
				void onCollision(Vec2 push) override;	//Called when a collision occurs.
				void beforeCollision() override;		//Called before any collisions are calculated to allow for resetting the jump conditions.

			private:
				bool m_onGround = false;				//If the player is on the ground.
				bool m_foundCollisionInTick = false;	//Used for checking when the player leaves the ground.
				bool m_swimming = false;				//If the player is swimming.
				int m_jumpHeld = 0;						//Used for determining how many frames the jump button has been held after the player jumps.

				AnimatorComponent* m_animator;			//Animator for walking, jumping, etc.

				void readKeys();						//Called to determine what buttons are pressed and apply velocity based on those buttons.

#if _DEBUG
				bool m_debug = false, m_debugKey = false;
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
			};

		};
	};
};

#endif