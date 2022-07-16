#include "NVDA.h"

void NVDA::readScreen()
{
}

void NVDA::textToSpeech(std::wstring string, bool saveHistory = true)
{
	if(saveHistory)
		lastMessage = string;
	nvdaController_speakText(string.c_str());
}

void NVDA::textToBraile(std::wstring string, bool saveHistory = true)
{
	nvdaController_brailleMessage(string.c_str());
}

void NVDA::readLastMessage()
{
	nvdaController_speakText(lastMessage.c_str());
}

void NVDA::setHelpMessage(std::wstring string)
{
	helpMessage = string;
}

void NVDA::readHelpMessage()
{
	nvdaController_speakText(helpMessage.c_str());
}

void NVDA::buildMessage(std::wstring string)
{
	builtMessage += string;
	builtMessage += L"\n";
}

void NVDA::cleanBuiltMessage()
{
	builtMessage = std::wstring();
}

std::wstring NVDA::getBuiltMessage()
{
	return builtMessage;
}

std::wstring NVDA::getLastMessage()
{
	return lastMessage;
}
