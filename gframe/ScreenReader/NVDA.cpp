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
