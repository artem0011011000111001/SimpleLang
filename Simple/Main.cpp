#include <iostream>
#include "Simple.h"
#include <fstream>
#include <string>

int main() { 
	std::string code = Simple::ReadCodeFromFile("code.simple");

	Simple::compile(code);

	return 0;
}