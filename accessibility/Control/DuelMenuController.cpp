#include "DuelMenuController.h"

namespace ygo {
	void static inline TriggerEvent(irr::gui::IGUIElement* target, irr::gui::EGUI_EVENT_TYPE type) {
		irr::SEvent event;
		event.EventType = irr::EET_GUI_EVENT;
		event.GUIEvent.EventType = type;
		event.GUIEvent.Caller = target;
		ygo::mainGame->device->postEventFromUser(event);
	}

	void DuelMenuController::ShowMenu(int flag, int x, int y) {
		if (!flag) {
			mainGame->wCmdMenu->setVisible(false);
			return;
		}
		int height = mainGame->Scale(1);
		auto increase = mainGame->Scale(21);
		if (flag & COMMAND_ACTIVATE) {
			mainGame->btnActivate->setVisible(true);
			mainGame->btnActivate->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnActivate->setVisible(false);
		if (flag & COMMAND_SUMMON) {
			mainGame->btnSummon->setVisible(true);
			mainGame->btnSummon->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSummon->setVisible(false);
		if (flag & COMMAND_SPSUMMON) {
			mainGame->btnSPSummon->setVisible(true);
			mainGame->btnSPSummon->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSPSummon->setVisible(false);
		if (flag & COMMAND_MSET) {
			mainGame->btnMSet->setVisible(true);
			mainGame->btnMSet->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnMSet->setVisible(false);
		if (flag & COMMAND_SSET) {
			if (!(mainGame->dField.clicked_card->type & TYPE_MONSTER))
				mainGame->btnSSet->setText(gDataManager->GetSysString(1153).data());
			else
				mainGame->btnSSet->setText(gDataManager->GetSysString(1159).data());
			mainGame->btnSSet->setVisible(true);
			mainGame->btnSSet->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnSSet->setVisible(false);
		if (flag & COMMAND_REPOS) {
			if (mainGame->dField.clicked_card->position & POS_FACEDOWN)
				mainGame->btnRepos->setText(gDataManager->GetSysString(1154).data());
			else if (mainGame->dField.clicked_card->position & POS_ATTACK)
				mainGame->btnRepos->setText(gDataManager->GetSysString(1155).data());
			else
				mainGame->btnRepos->setText(gDataManager->GetSysString(1156).data());
			mainGame->btnRepos->setVisible(true);
			mainGame->btnRepos->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnRepos->setVisible(false);
		if (flag & COMMAND_ATTACK) {
			mainGame->btnAttack->setVisible(true);
			mainGame->btnAttack->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnAttack->setVisible(false);
		if (flag & COMMAND_LIST) {
			mainGame->btnShowList->setVisible(true);
			mainGame->btnShowList->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnShowList->setVisible(false);
		if (flag & COMMAND_OPERATION) {
			mainGame->btnOperation->setVisible(true);
			mainGame->btnOperation->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnOperation->setVisible(false);
		if (flag & COMMAND_RESET) {
			mainGame->btnReset->setVisible(true);
			mainGame->btnReset->setRelativePosition(irr::core::vector2di(1, height));
			height += increase;
		}
		else mainGame->btnReset->setVisible(false);
		mainGame->dField.panel = mainGame->wCmdMenu;
		mainGame->wCmdMenu->setVisible(true);
		irr::core::vector2di mouse = mainGame->Resize(x, y);
		x = mouse.X;
		y = mouse.Y;
		mainGame->wCmdMenu->setRelativePosition(irr::core::recti(x - mainGame->Scale(20), y - mainGame->Scale(20) - height, x + mainGame->Scale(80), y - mainGame->Scale(20)));
	}

	void DuelMenuController::CloseDialog()
	{
		if (mainGame->wCardDisplay->isVisible()) {
			TriggerEvent(mainGame->btnDisplayOK, irr::gui::EGET_BUTTON_CLICKED);
			if (!mainGame->dField.display_cards.empty())
				mainGame->dField.display_cards.clear();
		}
	}

	void DuelMenuController::DisplayCards(const std::vector<ClientCard*>& field, const std::wstring& text)
	{
		/*mainGame->dField.display_cards.clear();
		EventVariables::indexLookedUpCard = 0;
		for (auto it = field.begin(); it != field.end(); ++it) {
			if (*it) {
				mainGame->dField.display_cards.push_back(*it);
			}
		}
		if (mainGame->dField.display_cards.size()) {
			mainGame->wCardDisplay->setText(fmt::format(L"{}({})", text, mainGame->dField.display_cards.size()).data());
			ShowLocationCard();
			if (text.compare(L"") != 0) {
				ScreenReader::getReader()->readScreen(fmt::format(L"{}{} cards", text, mainGame->dField.display_cards.size()).data(), false);
			}
			mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
		else
		{
			std::wstring nvdaString = fmt::format(L"There are no cards to display");
			ScreenReader::getReader()->readScreen(nvdaString.c_str(), false);
			DuelMenuController::CloseDialog();*/
		}
	}
	void DuelMenuController::DisplayCards(const std::vector<ChainInfo>& field, const std::wstring& text)
	{
		//mainGame->dField.display_cards.clear();
		//EventVariables::indexLookedUpCard = 0;
		//for (auto it = field.begin(); it != field.end(); ++it) {
		//	mainGame->dField.display_cards.push_back(it._Ptr->chain_card);
		//}
		//if (mainGame->dField.display_cards.size()) {
		//	mainGame->wCardDisplay->setText(fmt::format(L"{}({})", gDataManager->GetSysString(EventVariables::lookupFieldLocId), mainGame->dField.display_cards.size()).data());
		//	ShowLocationCard();
		//	mainGame->ShowCardInfo(mainGame->dField.display_cards[0]->code);
		}
	}

	void DuelMenuController::ShowLocationCard() {
		int startpos;
		size_t ct;
		if (mainGame->dField.display_cards.size() <= 5) {
			startpos = 30 + 125 * (5 - mainGame->dField.display_cards.size()) / 2;
			ct = mainGame->dField.display_cards.size();
		}
		else {
			startpos = 30;
			ct = 5;
		}
		for (size_t i = 0; i < ct; ++i) {
			auto& curstring = mainGame->stDisplayPos[i];
			auto& curcard = mainGame->dField.display_cards[i];
			curstring->enableOverrideColor(false);
			if (curcard->code)
				mainGame->imageLoading[mainGame->btnCardDisplay[i]] = curcard->code;
			else
				mainGame->btnCardDisplay[i]->setImage(mainGame->imageManager.tCover[curcard->controler]);
			mainGame->btnCardDisplay[i]->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 55, startpos + 120 + i * 125, 225));
			mainGame->btnCardDisplay[i]->setPressed(false);
			mainGame->btnCardDisplay[i]->setVisible(true);
			std::wstring text;
			if (curcard->location == LOCATION_OVERLAY) {
				text = fmt::format(L"{}[{}]({})", gDataManager->FormatLocation(curcard->overlayTarget->location, curcard->overlayTarget->sequence),
					curcard->overlayTarget->sequence + 1, curcard->sequence + 1);
			}
			else if (curcard->location) {
				text = fmt::format(L"{}[{}]", gDataManager->FormatLocation(curcard->location, curcard->sequence),
					curcard->sequence + 1);
			}
			curstring->setText(text.data());
			if (curcard->location == LOCATION_OVERLAY) {
				if (curcard->owner != curcard->overlayTarget->controler)
					curstring->setOverrideColor(skin::DUELFIELD_CARD_SELECT_WINDOW_OVERLAY_TEXT_VAL);
				if (curcard->overlayTarget->controler)
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
				else
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
			}
			else if (curcard->location == LOCATION_EXTRA || curcard->location == LOCATION_REMOVED) {
				if (curcard->position & POS_FACEDOWN)
					curstring->setOverrideColor(skin::DUELFIELD_CARD_SELECT_WINDOW_SET_TEXT_VAL);
				if (curcard->controler)
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
				else
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
			}
			else {
				if (curcard->controler)
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_OPPONENT_WINDOW_BACKGROUND_VAL);
				else
					curstring->setBackgroundColor(skin::DUELFIELD_CARD_SELF_WINDOW_BACKGROUND_VAL);
			}
			curstring->setVisible(true);
			curstring->setRelativePosition(mainGame->Scale<irr::s32>(startpos + i * 125, 30, startpos + 120 + i * 125, 50));
		}
		if (mainGame->dField.display_cards.size() <= 5) {
			for (int i = mainGame->dField.display_cards.size(); i < 5; ++i) {
				mainGame->btnCardDisplay[i]->setVisible(false);
				mainGame->stDisplayPos[i]->setVisible(false);
			}
			mainGame->scrDisplayList->setPos(0);
			mainGame->scrDisplayList->setVisible(false);
		}
		else {
			mainGame->scrDisplayList->setVisible(true);
			mainGame->scrDisplayList->setMin(0);
			mainGame->scrDisplayList->setMax((mainGame->dField.display_cards.size() - 5) * 10 + 9);
			mainGame->scrDisplayList->setPos(0);
		}
		mainGame->btnDisplayOK->setVisible(true);
		mainGame->PopupElement(mainGame->wCardDisplay);
	}
}
