#include "ScreenReader.h"

IScreenReader* ScreenReader::screenReader = nullptr;

void ScreenReader::setReader()
{
	//screenReader = new NVDA();
	screenReader = new TolkController();
}


IScreenReader* ScreenReader::getReader()
{
	setReader();
	return screenReader;
}
