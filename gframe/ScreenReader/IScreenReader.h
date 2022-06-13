
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
	virtual void readLastMessage() = 0;
};

#endif
