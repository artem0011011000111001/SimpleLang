#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>
#include <codecvt>

#pragma warning(disable : 4996)

int main(int argc, wchar_t* argv[]) {
	WString code;
	WString path;
	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = L"Upload_to_git.simple";
	}

	code = Simple::ReadCodeFromFile(path);
	Simple::compile(code);

	return 0;
}