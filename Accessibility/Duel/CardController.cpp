#include "CardController.h"
#include "../gframe/game.h"
#include <Control/EventHandler.h>

namespace ygo {
	CardController* CardController::GetCardController()
	{
		if (_cardController == nullptr)
			_cardController = new CardController();
		return _cardController;
	}

	void CardController::SetCard(ClientCard* card)
	{
		if (!card)
			return;
		_selectedCard = card;
	}

	void CardController::ShowCardOptions(int x, int y)
	{
		const int flag = _selectedCard->cmdFlag;
		if (!flag) {
			mainGame->wCmdMenu->setVisible(false);
			return;
		}
		int height = mainGame->Scale(1);
		const auto increase = mainGame->Scale(21);
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
		const irr::core::vector2di mouse = mainGame->Resize(x, y);
		x = mouse.X;
		y = mouse.Y;
		mainGame->wCmdMenu->setRelativePosition(irr::core::recti(x - mainGame->Scale(20), y - mainGame->Scale(20) - height, x + mainGame->Scale(80), y - mainGame->Scale(20)));
	}

	ClientCard* CardController::GetSelectedCard()
	{
		return _selectedCard;
	}

	void CardController::SetCardType(const AccessibilityFieldFocus::CardType type)
	{
		_cardType = type;
	}
}
