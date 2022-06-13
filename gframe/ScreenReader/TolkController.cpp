#include "TolkController.h"

void TolkController::readScreen()
{
}

void TolkController::textToSpeech(std::wstring string, bool saveHistory = true)
{
	if(saveHistory)
		lastMessage = string;
	Tolk_Output(string.c_str());
}

void TolkController::textToBraile(std::wstring string, bool saveHistory = true)
{
	Tolk_Output(string.c_str());
}

void TolkController::readLastMessage()
{
	Tolk_Output(lastMessage.c_str());
}
