#include "PlayerController.h"

#include "CardDisplayController.h"
#include "FieldController.h"
#include "IGUIButton.h"
#include "IGUIWindow.h"
#include "../gframe/game.h"
#include "../gframe/data_manager.h"
#include <IGUIEditBox.h>
#include "Configuration/AccessibilityConfiguration.h"
#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Models/CardModel.h"
#include "Models/FieldSlotModel.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"

namespace ygo {
	IEventHandler* PlayerController::_playerController = nullptr;
	IEventHandler* PlayerController::GetInstance()
	{
		if (_playerController == nullptr)
			_playerController = new PlayerController();
		return _playerController;
	}

	void PlayerController::KeyInputEvent(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == KeyboardConfiguration::Chat)
			StartChat();
		else if(event.KeyInput.Key == KeyboardConfiguration::PlayerInformation)
			PlayerInformation();
		else if(event.KeyInput.Key == KeyboardConfiguration::SeeTurn)
			SeeTurn();
	}

	void PlayerController::StartChat()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(88).data()), false);
		mainGame->env->setFocus(mainGame->ebChatInput);
	}

	void PlayerController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}

	bool PlayerController::HasEventKey(irr::EKEY_CODE key)
	{
		std::vector<int> keys = { KeyboardConfiguration::Chat, KeyboardConfiguration::PlayerInformation, KeyboardConfiguration::SeeTurn };
		if(std::find(keys.begin(), keys.end(), key) != keys.end())
			return true;
		return false;
	}


	void PlayerController::PlayerInformation()
	{
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(85).data(),mainGame->dInfo.lp[AccessibilityFieldFocus::Player::MAIN_PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(86).data(), mainGame->dInfo.lp[AccessibilityFieldFocus::Player::ENEMY_PLAYER]), false);
		ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(87).data(), mainGame->dInfo.time_left[AccessibilityFieldFocus::Player::MAIN_PLAYER]), false);
	}

	void PlayerController::SeeTurn(){
		if (mainGame->btnEP->isVisible() && mainGame->btnEP->isEnabled() && !mainGame->dInfo.selfnames.empty())
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(83).data(), mainGame->dInfo.selfnames.at(0)), false);
		else if (!mainGame->dInfo.opponames.empty())
			ScreenReader::getReader()->readScreen(fmt::format(gDataManager->GetAccessibilityString(84).data(), mainGame->dInfo.opponames.at(0)), false);
	}


}
