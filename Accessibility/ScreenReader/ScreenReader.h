#ifndef SCREENREADER_H
#define SCREENREADER_H


#include "IScreenReader.h"
#include "NVDA.h"
#include "TolkController.h"
#include "AccessibilityMessages.h"

class ScreenReader
{
public:

	static void setReader();
	static IScreenReader* getReader();

	ScreenReader() {};
	~ScreenReader() { delete screenReader; };
private:
	static IScreenReader* screenReader;
};

#endif
