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

		ScreenReader();

		static void macarena();
		static IScreenReader* getReader();
	
		~ScreenReader() { delete screenReader; };
};

#endif
