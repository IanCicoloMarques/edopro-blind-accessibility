#ifndef NVDA_H
#define NVDA_H

#pragma once
#include "IScreenReader.h"
#include "nvdaController.h"


class NVDA : public IScreenReader
{
	public:
		void readScreen();
		NVDA() {};
		~NVDA() {};


		void textToSpeech(std::wstring string);
		void textToBraile(std::wstring string);


};
#endif
