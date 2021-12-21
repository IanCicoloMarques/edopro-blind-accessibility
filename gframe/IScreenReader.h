
#ifndef ISCREENREADER_H
#define ISCREENREADER_H

#pragma once

#include <string>

class IScreenReader {


	public:

		virtual void readScreen() = 0;

		virtual void textToSpeech(std::wstring string) = 0;
		virtual void textToBraile(std::wstring string) = 0;

};

#endif
