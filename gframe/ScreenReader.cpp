#include "ScreenReader.h"

IScreenReader* ScreenReader::screenReader = nullptr;
void ScreenReader::setReader()
{
	//screenReader = new NVDA();
}


IScreenReader* ScreenReader::getReader()
{
	return screenReader;
}
