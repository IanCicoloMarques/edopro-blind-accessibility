#include "TolkController.h"

void TolkController::readScreen()
{
}

void TolkController::textToSpeech(std::wstring string)
{
	lastMessage = string;
	Tolk_Output(string.c_str());
}

void TolkController::textToBraile(std::wstring string)
{
	Tolk_Output(string.c_str());
}

void TolkController::readLastMessage()
{
	Tolk_Output(lastMessage.c_str());
}
