#include "NVDA.h"

void NVDA::readScreen()
{
}


void NVDA::textToSpeech()
{
	nvdaController_speakText(L"");
}

void NVDA::textToBraile()
{
	nvdaController_brailleMessage(L"");
}
