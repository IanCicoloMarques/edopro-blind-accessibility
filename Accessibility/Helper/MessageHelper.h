#ifndef MESSAGEHELPER_H
#define MESSAGEHELPER_H

#include <string>

#include "Configuration/MessageType.h"

namespace ygo
{
	class MessageHelper
	{
	public:
		static void ReadMessage(std::wstring message);
		static void ReadMessage(Message::MessageType message);
	private:
		static void WonRockPaperScissor();
		static void SelectYourTurn();
		static void NextMatch();
		static void CommaYesDotNo();
		static void CheckField();
		static void SelectChain();
		static void SelectPosition();
		static void SelectTribute();

	};
}

#endif
