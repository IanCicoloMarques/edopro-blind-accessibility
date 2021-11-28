#ifndef NVDA_H
#define NVDA_H

#pragma once
#include "IScreenReader.h"
#include "nvdaController.h"

class NVDA : public IScreenReader
{
	public:

		void readScreen();
		NVDA();
		~NVDA();

	private:

		void textToSpeech();
		void textToBraile();


};
#endif
