#include "Tree.h"
#include "../../../../Resources/Save/SaveManager.h"
#include "../../../../Objects/StateSaver.h"
#include "../../../Items/FloorItem.h"
#include "../../../../Components/Animation/AnimatorComponent.h"
#include "../../../../Utils/Time/GameTime.h"
#include "../../../InputDisplay/DisplayIconManager.h"

namespace GAME_NAME::Objects::Environment::Plants
{
	Tree::Tree(Vec2 position, Vec2 scale, Rendering::Sprite* sprite, size_t saveID, Rendering::Sprite* choppedSprite)
		: Interactable(TREE_INTERACT_KEY, InputManager::KEY_STATE_NONE, position, scale, sprite), GameObjectState(saveID),
		m_isChopped(false), m_choppedSprite(choppedSprite), m_rustles(0)
	{
		LoadState();

		AnimData rustleData;
		rustleData.Sprites.push_back(new Sprite(m_sprite->GetSpriteId() + 1));
		rustleData.Sprites.push_back(new Sprite(m_sprite->GetSpriteId() + 2));
		std::shared_ptr<GAME_NAME::Components::Animation::Animation> rustle(new GAME_NAME::Components::Animation::Animation(rustleData, 0.2));

		std::vector<std::shared_ptr<GAME_NAME::Components::Animation::Animation>> anims{ rustle };

		m_animator = new AnimatorComponent(anims);
	}

	void Tree::SaveState()
	{
		std::string saveStr = "";
		saveStr = saveStr + SAVE_MNG_STATE(m_isChopped);
		saveStr = saveStr + std::to_string(m_rustles);

		Resources::SaveManager::SaveLevelString(saveStr, m_objectSaveID);
	}

	void Tree::LoadState()
	{
		std::string result(SAVE_MNG_FALSE_STATE + "");
		Resources::SaveManager::GetLevelString(result, m_objectSaveID);
		setChopped(result[0] == SAVE_MNG_TRUE_STATE);

		if (result.length() > 1)
		{
			m_rustles = std::stoi(std::string("0") + result[1]);
		}
	}

	void Tree::Update(GLFWwindow* window)
	{
		Interactable::Update(window);

		m_animator->Update(window, this);
	}

	bool Tree::Chop()
	{
		if (m_isChopped) { return false; }

		setChopped(true);

		//DROP ITEMS
		Rustle();
		if (!m_toBeSaved)
		{
			StateSaver::RegisterToBeSaved(this);
		}

		//DROP LOGS

		return true;
	}

	bool Tree::Rustle()
	{
		m_rustleCounter += Utils::Time::GameTime::GetScaledDeltaTime();
		m_animator->SetCurrentAnimation(0);

		if (m_rustleCounter > 1.85f)
		{
			m_rustleCounter = 0;

			m_animator->SetCurrentAnimation(-1);

			if (m_rustles > 2) { return false; }
					//Increment counter until full to shake tree for period of time.

			m_rustles++;

			int c = 1 + (std::rand() * 3 / RAND_MAX);
			for (int i = 0; i < c; i++)
			{
				Items::FloorItem* myItem = new Items::FloorItem(m_position + Vec2::RandVec2(m_scale.X, m_scale.Y), Items::LEAVES, 0.5f);
				Renderer::InstantiateObject(Renderer::InstantiateGameObject(myItem, true, 1, false));
			}

			return true;
		}
		
		return false;
		

	}

	void Tree::onInteract(std::shared_ptr<Player::Player> player, InputManager::KEY_STATE state)
	{
		Input::DisplayIconManager::ShowKeyInputDisplay(Input::DisplayIconManager::INPUT_DISPLAY_KEY_E, TestGame::ThePlayer->GetPosition() + Vec2(TestGame::ThePlayer->GetScale() + Vec2(3, -5)), (char)(std::floor(m_rustleCounter * 10 / 1.85f)));

		if (state & InputManager::KEY_STATE_HELD)
		{
			bool suc = Rustle();
			if (suc && !m_toBeSaved)
			{
				StateSaver::RegisterToBeSaved(this);
			}
		}
		else if (state & InputManager::KEY_STATE_RELEASED)
		{
			m_animator->SetCurrentAnimation(-1);
			m_rustleCounter = 0;
		}


	}

	void Tree::setChopped(bool chopped)
	{
		if (m_isChopped == chopped) { return; }

		m_isChopped = chopped;

		//FLIP m_choppedSprite and m_sprite
		Rendering::Sprite* spCpy = new Rendering::Sprite(m_choppedSprite->GetSpriteId());

		delete m_choppedSprite;
		this->m_choppedSprite = m_sprite;

		m_sprite = spCpy;
	}
}


