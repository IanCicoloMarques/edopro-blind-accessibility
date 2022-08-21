#include "ScreenReader.h"

IScreenReader* ScreenReader::screenReader = nullptr;

void ScreenReader::setReader()
{
	screenReader = new TolkController();
}

IScreenReader* ScreenReader::getReader()
{
	if (screenReader == nullptr)
		setReader();
	return screenReader;
}
