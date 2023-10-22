#include "MessageHelper.h"

#include <utility>
#include "Control/EventHandler.h"
#include "ScreenReader/Messages/AccessibilityStringDictionary.h"

void ygo::MessageHelper::ReadMessage(std::wstring message)
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(std::move(message));
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::ReadMessage(Message::MessageType message)
{
	switch (message) {
		case Message::WON_ROCK_PAPERS_CISSORS:
			WonRockPaperScissor();
			break;
		case Message::SELECT_YOUR_TURN:
			SelectYourTurn();
			break;
		case Message::NEXT_MATCH:
			NextMatch();
			break;
	}
}

void ygo::MessageHelper::WonRockPaperScissor()
{
	if(EventHandler::PlayRockPaperScissor)
	{
		EventHandler::WonRockPaperScissor = true;
		ScreenReader::getReader()->readScreen(L"You won the rock paper scissors match");
	}
}

void ygo::MessageHelper::SelectYourTurn()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(47).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(48).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(49).data());
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::NextMatch()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(50).data());
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::CommaYesDotNo()
{
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(62).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(63).data());
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::CheckField()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(fmt::format(L"{}", gDataManager->GetSysString(202)));
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(265).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(266).data());
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::SelectChain()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(fmt::format(L"{}", gDataManager->GetAccessibilityString(Accessibility::Dict::Chain::CHAIN_SELECT_CARD).data()));
	ScreenReader::getReader()->buildMessage(fmt::format(L"{}", gDataManager->GetAccessibilityString(Accessibility::Dict::Chain::CHAIN_CANCEL).data()));
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::SelectPosition()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(267).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(268).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(269).data());
	ScreenReader::getReader()->readBuiltMessage();
}

void ygo::MessageHelper::SelectTribute()
{
	ScreenReader::getReader()->cleanBuiltMessage();
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(270).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(271).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(272).data());
	ScreenReader::getReader()->buildMessage(gDataManager->GetAccessibilityString(273).data());
	ScreenReader::getReader()->readBuiltMessage();
}
