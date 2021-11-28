#ifndef SCREENREADER_H
#define SCREENREADER_H


#pragma once
#include "IScreenReader.h"
#include "NVDA.h"

class ScreenReader
{
	private:
		static IScreenReader* screenReader;


	public:

		

		static void setReader();
		static IScreenReader* getReader();

		ScreenReader() {};
		~ScreenReader() { delete screenReader; };
};

#endif
