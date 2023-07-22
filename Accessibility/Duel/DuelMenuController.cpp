#include "DuelMenuController.h"
#include "../gframe/game.h"
#include "../gframe/CGUIImageButton/CGUIImageButton.h"
#include "../gframe/data_manager.h"
#include "../gframe/duelclient.h"
#include "Helper/ButtonHelper.h"
#include "ScreenReader/ScreenReader.h"
#include <IGUIWindow.h>
#include <IGUIComboBox.h>
#include <IGUIListBox.h>
#include <IGUICheckBox.h>

#include "Configuration/Keyboard/KeyboardConfiguration.h"
#include "Control/EventHandler.h"
#include "FieldFocus/AccessibilityFieldFocus.h"
#include "Helper/MouseHelper.h"

namespace ygo {
	IEventHandler* DuelMenuController::_duelMenuController = nullptr;
	IEventHandler* DuelMenuController::GetInstance()
	{
		if (_duelMenuController == nullptr)
			_duelMenuController = new DuelMenuController();
		return _duelMenuController;
	}

	static void FocusAndReadCheckBox(irr::gui::IGUICheckBox* chkbox) {
		if (!mainGame->env->hasFocus(chkbox))
			mainGame->env->setFocus(chkbox);
		const std::wstring nvdaString = fmt::format(L"{}", chkbox->getText());
		ScreenReader::getReader()->readScreen(nvdaString, false);
	}

	static void FocusAndReadGuiElement(irr::gui::IGUIElement* target, std::wstring message, bool saveHistory = false) {
		if (!mainGame->env->hasFocus(target))
			mainGame->env->setFocus(target);
		ScreenReader::getReader()->readScreen(std::move(message), saveHistory);
	}

	static void FocusAndReadGuiElement(irr::gui::IGUIElement* target, int stringCode, bool saveHistory = false) {
		if (!mainGame->env->hasFocus(target))
			mainGame->env->setFocus(target);
		ScreenReader::getReader()->readScreen(gDataManager->GetAccessibilityString(stringCode).data(), saveHistory);
	}

	void DuelMenuController::KeyInputEvent(const irr::SEvent& event)
	{
		if(event.KeyInput.Key == KeyboardConfiguration::BattlePhase && mainGame->btnBP->isVisible() && mainGame->btnBP->isEnabled())
			ChangeBattlePhase(AccessibilityFieldFocus::BattleStep::BP);
		else if(event.KeyInput.Key == KeyboardConfiguration::MainPhase2 && mainGame->btnM2->isVisible() && mainGame->btnM2->isEnabled())
			ChangeBattlePhase(AccessibilityFieldFocus::BattleStep::MP2);
		else if(event.KeyInput.Key == KeyboardConfiguration::EndTurn && mainGame->btnEP->isVisible() && mainGame->btnEP->isEnabled())
			ChangeBattlePhase(AccessibilityFieldFocus::BattleStep::ED);
		if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonYes && mainGame->btnFileSaveYes->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnFileSaveYes);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonYes && mainGame->btnYes->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnYes);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonFirstTurn && mainGame->btnFirst->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnFirst);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonAttackUp && mainGame->btnPSAU->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnPSAU);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonAttackDown && mainGame->btnPSAD->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnPSAD);
		else if(event.KeyInput.Key == KeyboardConfiguration::MouseRightClick)
			MouseHelper::Click(event, true);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonNo && mainGame->btnFileSaveNo->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnFileSaveNo);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonNo && mainGame->btnNo->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnNo);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonSecondTurn && mainGame->btnSecond->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnSecond);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonDefenseUp && mainGame->btnPSDU->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnPSDU);
		else if(event.KeyInput.Key == KeyboardConfiguration::MenuButtonDefenseDown && mainGame->btnPSDD->isTrulyVisible())
			ButtonHelper::ClickButton(mainGame->btnPSDD);
		else if(event.KeyInput.Key == irr::KEY_KEY_1 || event.KeyInput.Key == irr::KEY_NUMPAD1)
		{
			if(IsRockPaperScissorsAvailable())
				RockPaperScissors(event.KeyInput.Key);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_2 || event.KeyInput.Key == irr::KEY_NUMPAD2)
		{
			if(IsRockPaperScissorsAvailable())
				RockPaperScissors(event.KeyInput.Key);
			else
				SelectOption(1);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_3 || event.KeyInput.Key == irr::KEY_NUMPAD3)
		{
			if(IsRockPaperScissorsAvailable())
				RockPaperScissors(event.KeyInput.Key);
			else
				SelectOption(2);
		}
		else if(event.KeyInput.Key == irr::KEY_KEY_4 || event.KeyInput.Key == irr::KEY_NUMPAD4)
			SelectOption(3);
		else if(event.KeyInput.Key == irr::KEY_KEY_5 || event.KeyInput.Key == irr::KEY_NUMPAD5)
			SelectOption(4);
		else if(event.KeyInput.Key == irr::KEY_KEY_0 || event.KeyInput.Key == irr::KEY_NUMPAD0)
			ButtonHelper::ClickButton(mainGame->btnLeaveGame);
		else if(event.KeyInput.Key == irr::KEY_UP)
		{
			FocusOnMenus();
			if (mainGame->cbANNumber->isTrulyVisible())
				AnnounceNumber();
			else if (mainGame->lstANCard->isTrulyVisible())
				AnnounceCard();
			else if (_selectAttribute < _selectAttributeMax && CheckAttributeSelector())
				AttributeSelector(true);
			else if (_selectType < _selectTypeMax && CheckTypeSelector())
				RaceSelector(true);
			if (mainGame->btnOptionn->isTrulyVisible())
				ButtonHelper::ClickButton(mainGame->btnOptionn);
			else if (mainGame->btnOption[0]->isTrulyVisible() && mainGame->dField.selected_option - 1 < mainGame->dField.select_options.size()) {
				mainGame->dField.selected_option--;
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			}
			else if (mainGame->btnOption[0]->isTrulyVisible())
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
		}
		else if(event.KeyInput.Key == irr::KEY_DOWN){
			FocusOnMenus();
			if (mainGame->lstANCard->isTrulyVisible())
				AnnounceCard();
			else if (mainGame->cbANNumber->isTrulyVisible())
				AnnounceNumber();
			else if (_selectAttribute > 0 && CheckAttributeSelector())
				AttributeSelector(false);
			else if (_selectType > 0 && CheckTypeSelector())
				RaceSelector(false);
			else if (mainGame->btnOptionp->isTrulyVisible())
				ButtonHelper::ClickButton(mainGame->btnOptionp);
			else if (mainGame->btnOption[0]->isTrulyVisible() && mainGame->dField.selected_option + 1 < mainGame->dField.select_options.size()) {
				mainGame->dField.selected_option++;
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);
			}
			else if (mainGame->btnOption[0]->isTrulyVisible())
				ScreenReader::getReader()->readScreen(gDataManager->GetDesc(mainGame->dField.select_options[mainGame->dField.selected_option], mainGame->dInfo.compat_mode).data(), false);

		}
	}

	void DuelMenuController::GuiEvent(const irr::SEvent& event)
	{
		return;
	}
	void DuelMenuController::FocusOnMenus(){
		if (mainGame->cbANNumber->isTrulyVisible())
			FocusAndReadGuiElement(mainGame->cbANNumber, fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected())));
		else if (mainGame->ebANCard->isTrulyVisible())
			FocusAndReadGuiElement(mainGame->ebANCard, 111);
		else if (mainGame->wANRace->isTrulyVisible())
			FocusAndReadGuiElement(mainGame->wANRace, 112);
		else if (mainGame->wANAttribute->isTrulyVisible())
			FocusAndReadGuiElement(mainGame->wANAttribute, 113);
	};

	void DuelMenuController::AnnounceNumber() {
		if (mainGame->cbANNumber->isTrulyVisible())
		{
			if (!mainGame->env->hasFocus(mainGame->cbANNumber))
				mainGame->env->setFocus(mainGame->cbANNumber);
			const std::wstring nvdaString = fmt::format(L"{}", mainGame->cbANNumber->getItem(mainGame->cbANNumber->getSelected()));
			ScreenReader::getReader()->readScreen(nvdaString, false);
		}
	}

	void DuelMenuController::AnnounceCard() {
		if (mainGame->lstANCard->isTrulyVisible())
		{
			if (!mainGame->env->hasFocus(mainGame->lstANCard))
				mainGame->env->setFocus(mainGame->lstANCard);
			if (mainGame->lstANCard->getSelected() != -1) {
				const std::wstring nvdaString = fmt::format(L"{}", mainGame->lstANCard->getListItem(mainGame->lstANCard->getSelected()));
				ScreenReader::getReader()->readScreen(nvdaString, false);
			}
		}
	}

	void DuelMenuController::AttributeSelector(bool up) {
		if (_selectAttribute < _selectAttributeMax && CheckAttributeSelector())
		{
			if (up) {
				for (int i = _selectAttribute + 1; i < _selectAttributeMax; i++) {
					if (mainGame->chkAttribute[i]->isVisible()) {
						FocusAndReadCheckBox(mainGame->chkAttribute[i]);
						_selectAttribute = i;
						break;
					}
				}
			}
			else {
				for (int i = _selectAttribute - 1; i >= 0; i--) {
					if (mainGame->chkAttribute[i]->isVisible()) {
						FocusAndReadCheckBox(mainGame->chkAttribute[i]);
						_selectAttribute = i;
						break;
					}
				}
			}
		}
	}

	bool DuelMenuController::CheckAttributeSelector() {
		const bool isVisible = std::any_of(std::begin(mainGame->chkAttribute), std::end(mainGame->chkAttribute), [](auto& i){return i->isTrulyVisible();});
		return isVisible;
	}

	void DuelMenuController::RaceSelector(bool up) {
		if (_selectType < _selectTypeMax && CheckTypeSelector())
		{
			if (up) {
				for (int i = _selectType + 1; i < _selectTypeMax; i++) {
					if (mainGame->chkRace[i]->isVisible()) {
						FocusAndReadCheckBox(mainGame->chkRace[i]);
						_selectType = i;
						break;
					}
				}
			}
			else {
				for (int i = _selectType - 1; i >= 0; i--) {
					if (mainGame->chkRace[i]->isVisible()) {
						FocusAndReadCheckBox(mainGame->chkRace[i]);
						_selectType = i;
						break;
					}
				}
			}
		}
	}

	bool DuelMenuController::CheckTypeSelector() {
		const bool isVisible = std::any_of(std::begin(mainGame->chkRace), std::end(mainGame->chkRace), [](auto& i){return i->isTrulyVisible();});
		return isVisible;
	}

	bool DuelMenuController::IsRockPaperScissorsAvailable()
	{
		if(mainGame->btnHand[0]->isTrulyVisible())
			return true;
		return false;
	}

	void DuelMenuController::RockPaperScissors(irr::EKEY_CODE key)
	{
		if (mainGame->btnHand[0]->isTrulyVisible()) {
			int eventCode = 0;
			int messageCode = 0;
			if(key == irr::KEY_KEY_1) //Scissors
			{
				eventCode = 0;
				messageCode = 116;
			}
			else if(key == irr::KEY_KEY_2) //Rock
			{
				eventCode = 1;
				messageCode = 117;
			}
			else if(key == irr::KEY_KEY_3) //Paper
			{
				eventCode = 2;
				messageCode = 118;
			}
			ButtonHelper::ButtonHelper::ClickButton(mainGame->btnHand[eventCode]);
			const std::wstring nvdaString = fmt::format(gDataManager->GetAccessibilityString(messageCode).data());
			ScreenReader::getReader()->readScreen(nvdaString, false);
		}
	}

	void DuelMenuController::SelectOption(int i)
	{
		if (mainGame->btnOption[i]->isTrulyVisible()) {
			mainGame->dField.selected_option = i;
			SetResponseSelectedOption();
		}
	}

	void DuelMenuController::SetResponseSelectedOption() const
	{
		if (mainGame->dInfo.curMsg == MSG_SELECT_OPTION) {
			DuelClient::SetResponseI(mainGame->dField.selected_option);
		}
		else {
			int index = 0;
			while (mainGame->dField.activatable_cards[index] != mainGame->dField.command_card || mainGame->dField.activatable_descs[index].first != mainGame->dField.select_options[mainGame->dField.selected_option]) index++;
			if (mainGame->dInfo.curMsg == MSG_SELECT_IDLECMD) {
				DuelClient::SetResponseI((index << 16) + 5);
			}
			else if (mainGame->dInfo.curMsg == MSG_SELECT_BATTLECMD) {
				DuelClient::SetResponseI(index << 16);
			}
			else {
				DuelClient::SetResponseI(index);
			}
		}
		mainGame->HideElement(mainGame->wOptions, true);
	}

	void DuelMenuController::ChangeBattlePhase(AccessibilityFieldFocus::BattleStep bp)
	{
		if(bp == AccessibilityFieldFocus::BattleStep::BP && _battleStep != AccessibilityFieldFocus::BattleStep::BP && mainGame->btnBP->isEnabled())
		{
			ButtonHelper::ButtonHelper::ClickButton(mainGame->btnBP);
			_battleStep = bp;
		}
		else if(bp == AccessibilityFieldFocus::BattleStep::MP2 && _battleStep != AccessibilityFieldFocus::BattleStep::MP2 && mainGame->btnM2->isEnabled())
		{
			ButtonHelper::ButtonHelper::ClickButton(mainGame->btnM2);
			_battleStep = bp;
		}
		else if(bp == AccessibilityFieldFocus::BattleStep::ED && mainGame->btnEP->isEnabled())
		{
			ButtonHelper::ButtonHelper::ClickButton(mainGame->btnEP);
			_battleStep = bp;
		}
	}
}
