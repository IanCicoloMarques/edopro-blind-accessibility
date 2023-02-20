#ifndef ISCREENREADER_H
#define ISCREENREADER_H

//#pragma once

#include <string>
#include "StringBuilder.h"

class IScreenReader {
public:

	void readScreen(std::wstring string, bool saveHistory = true) {
		textToSpeech(StringBuilder::parseInput(string), saveHistory);
	}

	virtual void textToSpeech(std::wstring string, bool saveHistory = false) = 0;
	virtual void textToBraile(std::wstring string, bool saveHistory = false) = 0;
	virtual void setHelpMessage(std::wstring string) = 0;
	virtual void buildMessage(std::wstring string) = 0;
	virtual std::wstring getBuiltMessage() = 0;
	virtual std::wstring getLastMessage() = 0;
	virtual void cleanBuiltMessage() = 0;
	virtual void readHelpMessage() = 0;
	virtual void readLastMessage() = 0;
};

#endif
