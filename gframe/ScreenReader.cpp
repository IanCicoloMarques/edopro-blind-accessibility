#include "ScreenReader.h"

void ScreenReader::setReader()
{
	screenReader = new NVDA();
}


IScreenReader* ScreenReader::getReader()
{
	return screenReader;
}
