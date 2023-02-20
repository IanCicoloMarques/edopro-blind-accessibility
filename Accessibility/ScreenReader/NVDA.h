#ifndef NVDA_H
#define NVDA_H

#pragma once
#include "IScreenReader.h"
#include "../Readers/nvda-lib/nvdaController.h"

class NVDA : public IScreenReader
{
	public:
		NVDA() {};
		~NVDA() {};
		void readScreen();

	private:

		void textToSpeech(std::wstring string, bool saveHistory);
		void textToBraile(std::wstring string, bool saveHistory);
		void setHelpMessage(std::wstring string);
		void buildMessage(std::wstring string);
		void cleanBuiltMessage();
		std::wstring getBuiltMessage();
		std::wstring getLastMessage();
		void readHelpMessage();
		void readLastMessage();
		std::wstring lastMessage;
		std::wstring builtMessage;
		std::wstring helpMessage;
};
#endif
