#include "ScreenReader.h"

IScreenReader* ScreenReader::screenReader = nullptr;

void ScreenReader::setReader()
{
	//screenReader = new NVDA(); //TODO add configuration for other screenreaders
}


IScreenReader* ScreenReader::getReader()
{
	return screenReader = new NVDA(); //TODO add configuration for other screenreaders
}

