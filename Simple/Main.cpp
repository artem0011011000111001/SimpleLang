#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>
#include <codecvt>
int main(int argc, char** argv) {
	WString code;
	String path;
 	if (argc > 1) {
		path = argv[1];
	}
	else {
		path = "Upload_to_git.simple";
	}

	code = Simple::ReadCodeFromFile(path);
	Simple::compile(code);

	return 0;
}