
#ifndef ISCREENREADER_H
#define ISCREENREADER_H

class IScreenReader {


	public:

		virtual void readScreen() = 0;

	private:
		virtual void textToSpeech() = 0;
		virtual void textToBraile() = 0;

};

#endif
