#include "NVDA.h"

void NVDA::readScreen()
{
}

void NVDA::textToSpeech(std::wstring string)
{
	nvdaController_speakText(string.c_str());
}

void NVDA::textToBraile(std::wstring string)
{
	nvdaController_brailleMessage(string.c_str());
}
