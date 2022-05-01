#ifndef TOLKCONTROLLER_H
#define TOLKCONTROLLER_H

#include "../ScreenReader/src/Tolk.h"
#include "IScreenReader.h"

class TolkController : public IScreenReader
{
public:
	TolkController() {
		Tolk_Load();
	};
	~TolkController() {
		Tolk_Unload();
	};
	void readScreen();

private:

	void textToSpeech(std::wstring string);
	void textToBraile(std::wstring string);
	void readLastMessage();
	std::wstring lastMessage;

};
#endif
