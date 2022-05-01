#ifndef NVDA_H
#define NVDA_H

#pragma once
#include "IScreenReader.h"
#include "nvdaController.h"

class NVDA : public IScreenReader
{
	public:
		NVDA() {};
		~NVDA() {};
		void readScreen();

	private:

		void textToSpeech(std::wstring string);
		void textToBraile(std::wstring string);
		void readLastMessage();
		std::wstring lastMessage;

};
#endif
