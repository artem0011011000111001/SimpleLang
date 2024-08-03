#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

	String code, path;
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