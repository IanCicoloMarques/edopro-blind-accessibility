
#ifndef ISCREENREADER_H
#define ISCREENREADER_H

//#pragma once

#include <string>
#include "StringBuilder.h"

class IScreenReader {
public:

	void readScreen(std::wstring string) {
		textToSpeech(StringBuilder::parseInput(string));
	}

	virtual void textToSpeech(std::wstring string) = 0;
	virtual void textToBraile(std::wstring string) = 0;
	virtual void readLastMessage() = 0;
};

#endif
