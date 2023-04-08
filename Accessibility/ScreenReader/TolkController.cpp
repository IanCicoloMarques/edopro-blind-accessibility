#include "TolkController.h"

TolkController::TolkController()
{
	Tolk_Load();
}

TolkController::~TolkController()
{
	Tolk_Unload();
}

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

void TolkController::readHelpMessage()
{
	Tolk_Output(helpMessage.c_str());
}

void TolkController::setHelpMessage(std::wstring string)
{
	helpMessage = string;
}

void TolkController::buildMessage(std::wstring string)
{
	builtMessage += string;
	builtMessage += L",\n";
}

void TolkController::cleanBuiltMessage()
{
	builtMessage = std::wstring();
}

std::wstring TolkController::getBuiltMessage()
{
	return builtMessage;
}

std::wstring TolkController::getLastMessage()
{
	return lastMessage;
}
