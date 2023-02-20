#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <string>

class StringBuilder
{
	public:
		static std::wstring parseInput(std::wstring string){
			return string;
		}
		static std::wstring getBuiltMessage();
		static void AddLine(std::wstring string);
		static void cleanBuiltMessage();
private:
		static std::wstring builtMessage;
};

#endif
