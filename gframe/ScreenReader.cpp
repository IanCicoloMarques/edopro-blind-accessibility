#include "ScreenReader.h"

ScreenReader::ScreenReader()
{
}

void ScreenReader::setReader()
{
	screenReader = new NVDA();
}


IScreenReader* ScreenReader::getReader()
{
	return screenReader;
}
